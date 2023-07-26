#include "Pch.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace xe;
using namespace xe::Math;

void xe::Graphics::StandardEffect::Initialize(const std::filesystem::path& path)
{
	_transformBuffer.Initialize();
	_lightingBuffer.Initialize();
	_materialBuffer.Initialize();
	_settingsBuffer.Initialize();

	_vertexShader.Initialize<Vertex>(path);
	_pixelShader.Initialize(path);
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::StandardEffect::Terminate()
{
	_sampler.Terminate();
	_pixelShader.Terminate();
	_vertexShader.Terminate();

	_settingsBuffer.Terminate();
	_materialBuffer.Terminate();
	_lightingBuffer.Terminate();
	_transformBuffer.Terminate();
}

void xe::Graphics::StandardEffect::Begin()
{
	ASSERT(_camera, "Standard Effect -> no camera set");

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

void xe::Graphics::StandardEffect::End()
{
}

void xe::Graphics::StandardEffect::Draw(const RenderObject& renderObject)
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
	settingsData.useNormalMap = _settingsData.useNormalMap > 0 && renderObject.normalMapID != 0;
	settingsData.useDisplMap = _settingsData.useDisplMap > 0 && renderObject.displMapID != 0;
	settingsData.displWeight = _settingsData.displWeight;
	_settingsBuffer.Update(settingsData);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.normalMapID, 1);
	TextureManager::BindVertexShader(renderObject.displMapID, 2);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::StandardEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}

void xe::Graphics::StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	_directionalLight = &directionalLight;
}

void xe::Graphics::StandardEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Standard##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = _settingsData.useDiffuseMap > 0;
		if (ImGui::Checkbox("Use Diffuse Map##", &useDiffuseMap))
		{
			_settingsData.useDiffuseMap = (useDiffuseMap) ? 1: 0;
		}
		bool useNormalMap = _settingsData.useNormalMap > 0;
		if (ImGui::Checkbox("Use Normal Map##", &useNormalMap))
		{
			_settingsData.useNormalMap = (useNormalMap) ? 1 : 0;
		}
		bool useDisplMap = _settingsData.useDisplMap > 0;
		if (ImGui::Checkbox("Use Displace Map##", &useDisplMap))
		{
			_settingsData.useDisplMap = (useDisplMap) ? 1 : 0;
		}
		ImGui::DragFloat("Displacement Weight##", &_settingsData.displWeight, 0.1f, 0.0f, 2.0f);
	}
#endif
}
