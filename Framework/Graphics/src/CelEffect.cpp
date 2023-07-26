#include "Pch.h"
#include "CelEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace xe;
using namespace xe::Math;

void xe::Graphics::CelEffect::Initialize(const std::filesystem::path& path)
{
	_transformBuffer.Initialize();
	_lightingBuffer.Initialize();
	_materialBuffer.Initialize();
	_settingsBuffer.Initialize();

	_vertexShader.Initialize<Vertex>(path);
	_pixelShader.Initialize(path);
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::CelEffect::Terminate()
{
	_sampler.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();

	_settingsBuffer.Terminate();
	_materialBuffer.Terminate();
	_lightingBuffer.Terminate();
	_transformBuffer.Terminate();
}

void xe::Graphics::CelEffect::Begin()
{
	ASSERT(_camera, "Cel Effect -> no camera set");

	_vertexShader.Bind();
	_pixelShader.Bind();

	_transformBuffer.BindVertexShader(0);
	
	_lightingBuffer.BindVertexShader(1);
	_lightingBuffer.BindPixelShader(1);

	_materialBuffer.BindPixelShader(2);

	_settingsBuffer.BindVertexShader(3);
	_settingsBuffer.BindPixelShader(3);

	_sampler.BindVertexShader(0);
	_sampler.BindPixelShader(0);
}

void xe::Graphics::CelEffect::End()
{
}

void xe::Graphics::CelEffect::Draw(const RenderObject& renderObject)
{
	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = _camera->GetViewMatrix();
	const Matrix4& matProj = _camera->GetProjectionMatrix();

	TransfromData transformData;
	transformData.world = xe::Math::Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = _camera->GetPosition();
	
	_transformBuffer.Update(transformData);
	_lightingBuffer.Update(*_directionalLight);
	_materialBuffer.Update(renderObject.material);
	SettingsData settingsData;
	settingsData.useDiffuseMap = _settingsData.useDiffuseMap > 0 && renderObject.diffuseMapID != 0;
	_settingsBuffer.Update(settingsData);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::CelEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}

void xe::Graphics::CelEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	_directionalLight = &directionalLight;
}

void xe::Graphics::CelEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Cel##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = _settingsData.useDiffuseMap > 0;
		if (ImGui::Checkbox("Use Diffuse Map##", &useDiffuseMap))
		{
			_settingsData.useDiffuseMap = (useDiffuseMap) ? 1: 0;
		}
	}
#endif
}
