#include "Pch.h"
#include "WaterEffect.h"

#include "Camera.h"
#include "Texture.h"
#include "RenderObject.h"

using namespace xe::Math;

void xe::Graphics::WaterEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Water.fx";
	_vertexShader.Initialize<Vertex>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_transformBuffer.Initialize();
	_lightingBuffer.Initialize();
	_materialBuffer.Initialize();
	_settingsBuffer.Initialize();
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::WaterEffect::Terminate()
{
	_sampler.Terminate();
	_settingsBuffer.Terminate();
	_materialBuffer.Terminate();
	_lightingBuffer.Terminate();
	_transformBuffer.Terminate();

	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::WaterEffect::Begin()
{
	_vertexShader.Bind();
	_pixelShader.Bind();

	_transformBuffer.BindVertexShader(0);

	_lightingBuffer.BindPixelShader(1);
	_lightingBuffer.BindVertexShader(1);

	_materialBuffer.BindPixelShader(2);

	_settingsBuffer.BindPixelShader(3);
	_settingsBuffer.BindVertexShader(3);

	_sampler.BindPixelShader(0);
	_sampler.BindVertexShader(0);
}

void xe::Graphics::WaterEffect::End()
{
	if (_shadowMap != nullptr)
	{
		Texture::UnbindPixelShader(2);
	}
}

void xe::Graphics::WaterEffect::Update(const float deltaTime)
{
	_settingsData.time += deltaTime;
}

void xe::Graphics::WaterEffect::Draw(const RenderObject& renderObject)
{
	ASSERT(_camera != nullptr, "TerrainEffect: no camera specified");
	ASSERT(_directionalLight != nullptr, "TerrainEffect: no light specified");

	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = _camera->GetViewMatrix();
	const Matrix4& matProj = _camera->GetProjectionMatrix();

	TransfromData transformData;
	transformData.world = xe::Math::Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = _camera->GetPosition();
	if (_shadowMap != nullptr && _lightCamera != nullptr)
	{
		const xe::Math::Matrix4& matLightView = _lightCamera->GetViewMatrix();
		const xe::Math::Matrix4& matLightProj = _lightCamera->GetProjectionMatrix();
		transformData.lwvp = Transpose(matWorld * matLightView * matLightProj);
	}

	SettingsData settingsData;
	settingsData.wavelength = _settingsData.wavelength;
	settingsData.amplitude = _settingsData.amplitude;
	settingsData.waveSpeed = _settingsData.waveSpeed;
	settingsData.textureSpeed = _settingsData.textureSpeed;
	settingsData.time = _settingsData.time;

	_transformBuffer.Update(transformData);
	_settingsBuffer.Update(settingsData);
	_lightingBuffer.Update(*_directionalLight);
	_materialBuffer.Update(renderObject.material);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.specMapID, 1);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::WaterEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Water##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Wavelength Modifier##Water", &_settingsData.wavelength, 0.01f);
		ImGui::DragFloat("Amplitude Modifier##Water", &_settingsData.amplitude, 0.01f);
		ImGui::DragFloat("Wave Speed Modifier##Water", &_settingsData.waveSpeed, 0.01f);
		ImGui::DragFloat("Texture Speed Modifier##Water", &_settingsData.textureSpeed, 0.01f);
		ImGui::Text("Time: %.2f", _settingsData.time);
	}
#endif // _DEBUG
}

void xe::Graphics::WaterEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}

void xe::Graphics::WaterEffect::SetLightCamera(const Camera& camera)
{
	_lightCamera = &camera;
}

void xe::Graphics::WaterEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	_directionalLight = &directionalLight;
}

void xe::Graphics::WaterEffect::SetShadowMap(const Texture& shadowMap)
{
	_shadowMap = &shadowMap;
}