#include "Pch.h"
#include "CelEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace xe;
using namespace xe::Math;

void xe::Graphics::CelEffect::Initialize(const std::filesystem::path& path)
{
	m_transformBuffer.Initialize();
	m_lightingBuffer.Initialize();
	m_materialBuffer.Initialize();
	m_settingsBuffer.Initialize();

	m_vertexShader.Initialize<Vertex>(path);
	m_pixelShader.Initialize(path);
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::CelEffect::Terminate()
{
	m_sampler.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();

	m_settingsBuffer.Terminate();
	m_materialBuffer.Terminate();
	m_lightingBuffer.Terminate();
	m_transformBuffer.Terminate();
}

void xe::Graphics::CelEffect::Begin()
{
	ASSERT(m_camera, "Cel Effect -> no camera set");

	m_vertexShader.Bind();
	m_pixelShader.Bind();

	m_transformBuffer.BindVertexShader(0);
	
	m_lightingBuffer.BindVertexShader(1);
	m_lightingBuffer.BindPixelShader(1);

	m_materialBuffer.BindPixelShader(2);

	m_settingsBuffer.BindVertexShader(3);
	m_settingsBuffer.BindPixelShader(3);

	m_sampler.BindVertexShader(0);
	m_sampler.BindPixelShader(0);
}

void xe::Graphics::CelEffect::End()
{
}

void xe::Graphics::CelEffect::Draw(const RenderObject& renderObject)
{
	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = m_camera->GetViewMatrix();
	const Matrix4& matProj = m_camera->GetProjectionMatrix();

	TransfromData transformData;
	transformData.world = xe::Math::Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = m_camera->GetPosition();
	
	m_transformBuffer.Update(transformData);
	m_lightingBuffer.Update(*m_directionalLight);
	m_materialBuffer.Update(renderObject.material);
	SettingsData settingsData;
	settingsData.useDiffuseMap = m_settingsData.useDiffuseMap > 0 && renderObject.diffuseMapID != 0;
	m_settingsBuffer.Update(settingsData);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::CelEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}

void xe::Graphics::CelEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_directionalLight = &directionalLight;
}

void xe::Graphics::CelEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Cel##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = m_settingsData.useDiffuseMap > 0;
		if (ImGui::Checkbox("Use Diffuse Map##", &useDiffuseMap))
		{
			m_settingsData.useDiffuseMap = (useDiffuseMap) ? 1: 0;
		}
	}
#endif
}
