#include "Pch.h"
#include "TerrainEffect.h"

#include "Camera.h"
#include "Texture.h"
#include "RenderObject.h"

using namespace xe::Math;

void xe::Graphics::TerrainEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Terrain.fx";
	m_vertexShader.Initialize<Vertex>(shaderFile);
	m_pixelShader.Initialize(shaderFile);

	m_transformBuffer.Initialize();
	m_lightingBuffer.Initialize();
	m_materialBuffer.Initialize();
	m_settingsBuffer.Initialize();
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::TerrainEffect::Terminate()
{
	m_sampler.Terminate();
	m_settingsBuffer.Terminate();
	m_materialBuffer.Terminate();
	m_lightingBuffer.Terminate();
	m_transformBuffer.Terminate();

	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::TerrainEffect::Begin()
{
	m_vertexShader.Bind();
	m_pixelShader.Bind();

	m_transformBuffer.BindVertexShader(0);

	m_lightingBuffer.BindPixelShader(1);
	m_lightingBuffer.BindVertexShader(1);

	m_materialBuffer.BindPixelShader(2);

	m_settingsBuffer.BindPixelShader(3);
	m_settingsBuffer.BindVertexShader(3);

	m_sampler.BindPixelShader(0);
	m_sampler.BindVertexShader(0);
}

void xe::Graphics::TerrainEffect::End()
{
	if (m_shadowMap != nullptr)
	{
		Texture::UnbindPixelShader(2);
	}
}

void xe::Graphics::TerrainEffect::Draw(const RenderObject& renderObject)
{
	ASSERT(m_camera != nullptr, "TerrainEffect: no camera specified");
	ASSERT(m_directionalLight != nullptr, "TerrainEffect: no light specified");

	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = m_camera->GetViewMatrix();
	const Matrix4& matProj = m_camera->GetProjectionMatrix();

	TransfromData transformData;
	transformData.world = xe::Math::Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = m_camera->GetPosition();
	if (m_shadowMap != nullptr && m_lightCamera != nullptr)
	{
		const xe::Math::Matrix4& matLightView = m_lightCamera->GetViewMatrix();
		const xe::Math::Matrix4& matLightProj = m_lightCamera->GetProjectionMatrix();
		transformData.lwvp = Transpose(matWorld * matLightView * matLightProj);
	}

	SettingsData settingsData;
	settingsData.useShadowMap = (m_settingsData.useShadowMap > 0 && m_shadowMap != nullptr) ? 1 : 0;
	settingsData.depthBias = m_settingsData.depthBias;
	if (settingsData.useShadowMap)
	{
		m_shadowMap->BindPixelShader(2);
	}

	m_transformBuffer.Update(transformData);
	m_settingsBuffer.Update(settingsData);
	m_lightingBuffer.Update(*m_directionalLight);
	m_materialBuffer.Update(renderObject.material);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.specMapID, 1);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::TerrainEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Terrain##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useShadowMap = m_settingsData.useShadowMap > 0;
		if (ImGui::Checkbox("Use Shadow Map##Terrain", &useShadowMap))
		{
			m_settingsData.useShadowMap = (useShadowMap) ? 1 : 0;
		}
		ImGui::DragFloat("Depth Bias##Terrain", &m_settingsData.depthBias, 0.0000001f, 0.f, 1.f, "%.6f");
	}
#endif // _DEBUG
}

void xe::Graphics::TerrainEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}

void xe::Graphics::TerrainEffect::SetLightCamera(const Camera& camera)
{
	m_lightCamera = &camera;
}

void xe::Graphics::TerrainEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_directionalLight = &directionalLight;
}

void xe::Graphics::TerrainEffect::SetShadowMap(const Texture& shadowMap)
{
	m_shadowMap = &shadowMap;
}
