#include "Pch.h"
#include "TerrainEffect.h"

#include "Camera.h"
#include "Texture.h"
#include "RenderObject.h"

using namespace xe::Math;

void xe::Graphics::TerrainEffect::Initialize()
{
	std::filesystem::path shaderFile = L"../../Assets/Shaders/Terrain.fx";
	_vertexShader.Initialize<Vertex>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_transformBuffer.Initialize();
	_lightingBuffer.Initialize();
	_materialBuffer.Initialize();
	_settingsBuffer.Initialize();
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::TerrainEffect::Terminate()
{
	_sampler.Terminate();
	_settingsBuffer.Terminate();
	_materialBuffer.Terminate();
	_lightingBuffer.Terminate();
	_transformBuffer.Terminate();

	_pixelShader.Terminate();
	_vertexShader.Terminate();
}

void xe::Graphics::TerrainEffect::Begin()
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

void xe::Graphics::TerrainEffect::End()
{
	if (_shadowMap != nullptr)
	{
		Texture::UnbindPixelShader(2);
	}
}

void xe::Graphics::TerrainEffect::Draw(const RenderObject& renderObject)
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
	settingsData.useShadowMap = (_settingsData.useShadowMap > 0 && _shadowMap != nullptr) ? 1 : 0;
	settingsData.depthBias = _settingsData.depthBias;
	if (settingsData.useShadowMap)
	{
		_shadowMap->BindPixelShader(2);
	}

	_transformBuffer.Update(transformData);
	_settingsBuffer.Update(settingsData);
	_lightingBuffer.Update(*_directionalLight);
	_materialBuffer.Update(renderObject.material);

	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.specMapID, 1);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::TerrainEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Terrain##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useShadowMap = _settingsData.useShadowMap > 0;
		if (ImGui::Checkbox("Use Shadow Map##Terrain", &useShadowMap))
		{
			_settingsData.useShadowMap = (useShadowMap) ? 1 : 0;
		}
		ImGui::DragFloat("Depth Bias##Terrain", &_settingsData.depthBias, 0.0000001f, 0.f, 1.f, "%.6f");
	}
#endif // _DEBUG
}

void xe::Graphics::TerrainEffect::SetCamera(const Camera& camera)
{
	_camera = &camera;
}

void xe::Graphics::TerrainEffect::SetLightCamera(const Camera& camera)
{
	_lightCamera = &camera;
}

void xe::Graphics::TerrainEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	_directionalLight = &directionalLight;
}

void xe::Graphics::TerrainEffect::SetShadowMap(const Texture& shadowMap)
{
	_shadowMap = &shadowMap;
}
