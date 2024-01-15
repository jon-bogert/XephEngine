#include "Pch.h"
#include "WaterEffect.h"

#include "Camera.h"
#include "Texture.h"
#include "RenderObject.h"

using namespace xe::Math;

void xe::Graphics::WaterEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Water.fx";
	m_vertexShader.Initialize<Vertex>(shaderFile);
	m_pixelShader.Initialize(shaderFile);

	m_transformBuffer.Initialize();
	m_lightingBuffer.Initialize();
	m_materialBuffer.Initialize();
	m_settingsBuffer.Initialize();
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::WaterEffect::Terminate()
{
	m_sampler.Terminate();
	m_settingsBuffer.Terminate();
	m_materialBuffer.Terminate();
	m_lightingBuffer.Terminate();
	m_transformBuffer.Terminate();

	m_pixelShader.Terminate();
	m_vertexShader.Terminate();
}

void xe::Graphics::WaterEffect::Begin()
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

void xe::Graphics::WaterEffect::End()
{
	if (m_shadowMap != nullptr)
	{
		Texture::UnbindPixelShader(2);
	}
}

void xe::Graphics::WaterEffect::Update(const float deltaTime)
{
	m_settingsData.time += deltaTime;
}

void xe::Graphics::WaterEffect::Draw(const RenderObject& renderObject)
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
	settingsData.wavelength = m_settingsData.wavelength;
	settingsData.amplitude = m_settingsData.amplitude;
	settingsData.waveSpeed = m_settingsData.waveSpeed;
	settingsData.textureSpeed = m_settingsData.textureSpeed;
	settingsData.time = m_settingsData.time;

	m_transformBuffer.Update(transformData);
	m_settingsBuffer.Update(settingsData);
	m_lightingBuffer.Update(*m_directionalLight);
	m_materialBuffer.Update(renderObject.material);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.specMapID, 1);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::WaterEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Water##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Wavelength Modifier##Water", &m_settingsData.wavelength, 0.01f);
		ImGui::DragFloat("Amplitude Modifier##Water", &m_settingsData.amplitude, 0.01f);
		ImGui::DragFloat("Wave Speed Modifier##Water", &m_settingsData.waveSpeed, 0.01f);
		ImGui::DragFloat("Texture Speed Modifier##Water", &m_settingsData.textureSpeed, 0.01f);
		ImGui::Text("Time: %.2f", m_settingsData.time);
	}
#endif // _DEBUG
}

void xe::Graphics::WaterEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}

void xe::Graphics::WaterEffect::SetLightCamera(const Camera& camera)
{
	m_lightCamera = &camera;
}

void xe::Graphics::WaterEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_directionalLight = &directionalLight;
}

void xe::Graphics::WaterEffect::SetShadowMap(const Texture& shadowMap)
{
	m_shadowMap = &shadowMap;
}