#include "Pch.h"
#include "StandardEffect.h"
#include "Camera.h"
#include "RenderObject.h"
#include "VertexTypes.h"
#include "AnimationUtil.h"

using namespace xe;
using namespace xe::Math;

static constexpr size_t MAX_BONE_COUNT = 256;

void xe::Graphics::StandardEffect::Initialize(const std::filesystem::path& path)
{
	m_transformBuffer.Initialize();
	m_lightingBuffer.Initialize();
	m_materialBuffer.Initialize();
	m_settingsBuffer.Initialize();
	m_boneTransformBuffer.Initialize(MAX_BONE_COUNT * sizeof(xe::Math::Matrix4));

	m_vertexShader.Initialize<Vertex>(path);
	m_pixelShader.Initialize(path);
	m_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void xe::Graphics::StandardEffect::Terminate()
{
	m_sampler.Terminate();
	m_pixelShader.Terminate();
	m_vertexShader.Terminate();

	m_boneTransformBuffer.Terminate();
	m_settingsBuffer.Terminate();
	m_materialBuffer.Terminate();
	m_lightingBuffer.Terminate();
	m_transformBuffer.Terminate();
}

void xe::Graphics::StandardEffect::Begin()
{
	ASSERT(m_camera, "Standard Effect -> no camera set");

	m_vertexShader.Bind();
	m_pixelShader.Bind();

	m_transformBuffer.BindVertexShader(0);
	
	m_lightingBuffer.BindVertexShader(1);
	m_lightingBuffer.BindPixelShader(1);

	m_materialBuffer.BindPixelShader(2);

	m_settingsBuffer.BindVertexShader(3);
	m_settingsBuffer.BindPixelShader(3);

	m_boneTransformBuffer.BindVertexShader(4);

	m_sampler.BindVertexShader(0);
	m_sampler.BindPixelShader(0);
}

void xe::Graphics::StandardEffect::End()
{
	if (m_shadowMap != nullptr)
	{
		Texture::UnbindPixelShader(4);
	}
}

void xe::Graphics::StandardEffect::Draw(const RenderObject& renderObject)
{
	const Matrix4& matWorld = renderObject.transform.Matrix();
	const Matrix4& matView = m_camera->GetViewMatrix();
	const Matrix4& matProj = m_camera->GetProjectionMatrix();

	SettingsData settingsData;
	settingsData.useDiffuseMap = m_settingsData.useDiffuseMap > 0 && renderObject.diffuseMapID != 0;
	settingsData.useNormalMap = m_settingsData.useNormalMap > 0 && renderObject.normalMapID != 0;
	settingsData.useDisplMap = m_settingsData.useDisplMap > 0 && renderObject.displMapID != 0;
	settingsData.displWeight = m_settingsData.displWeight;
	settingsData.useSpecMap = m_settingsData.useSpecMap > 0 && renderObject.specMapID != 0;
	settingsData.useShadowMap = m_settingsData.useShadowMap > 0 && m_shadowMap != nullptr;
	settingsData.depthBias = m_settingsData.depthBias;
	settingsData.useSkinning = m_settingsData.useSkinning > 0 && renderObject.skeleton != nullptr && renderObject.animator != nullptr;
	m_settingsBuffer.Update(settingsData);

	TransfromData transformData;
	transformData.world = xe::Math::Transpose(matWorld);
	transformData.wvp = Transpose(matWorld * matView * matProj);
	transformData.viewPosition = m_camera->GetPosition();
	if (settingsData.useShadowMap)
	{
		const xe::Math::Matrix4& matLightView = m_lightCamera->GetViewMatrix();
		const xe::Math::Matrix4& matLightProj = m_lightCamera->GetProjectionMatrix();
		transformData.lwvp = Transpose(matWorld * matLightView * matLightProj);

		m_shadowMap->BindPixelShader(4);
	}
	m_transformBuffer.Update(transformData);
	if (settingsData.useSkinning)
	{
		AnimationUtil::BoneTransforms boneTransforms;
		AnimationUtil::ComputeBoneTransform(renderObject.modelID, boneTransforms, renderObject.animator);
		AnimationUtil::ApplyBoneOffsets(renderObject.modelID, boneTransforms);

		for (auto& transform : boneTransforms)
		{
			transform = Transpose(transform);
		}
		boneTransforms.resize(MAX_BONE_COUNT);
		m_boneTransformBuffer.Update(boneTransforms.data());
	}
	m_lightingBuffer.Update(*m_directionalLight);
	m_materialBuffer.Update(renderObject.material);


	TextureManager::BindPixelShader(renderObject.diffuseMapID, 0);
	TextureManager::BindPixelShader(renderObject.normalMapID, 1);
	TextureManager::BindVertexShader(renderObject.displMapID, 2);
	TextureManager::BindPixelShader(renderObject.specMapID, 3);

	renderObject.meshBuffer.Draw();
}

void xe::Graphics::StandardEffect::SetCamera(const Camera& camera)
{
	m_camera = &camera;
}

void xe::Graphics::StandardEffect::SetLightCamera(const Camera& camera)
{
	m_lightCamera = &camera;
}

void xe::Graphics::StandardEffect::SetDirectionalLight(const DirectionalLight& directionalLight)
{
	m_directionalLight = &directionalLight;
}

void xe::Graphics::StandardEffect::SetShadowMap(const Texture& shadowMap)
{
	m_shadowMap = &shadowMap;
}

void xe::Graphics::StandardEffect::DebugUI()
{
#ifdef _DEBUG
	if (ImGui::CollapsingHeader("Standard##Effect", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool useDiffuseMap = m_settingsData.useDiffuseMap > 0;
		if (ImGui::Checkbox("Use Diffuse Map##", &useDiffuseMap))
		{
			m_settingsData.useDiffuseMap = (useDiffuseMap) ? 1: 0;
		}
		bool useNormalMap = m_settingsData.useNormalMap > 0;
		if (ImGui::Checkbox("Use Normal Map##", &useNormalMap))
		{
			m_settingsData.useNormalMap = (useNormalMap) ? 1 : 0;
		}
		bool useDisplMap = m_settingsData.useDisplMap > 0;
		if (ImGui::Checkbox("Use Displace Map##", &useDisplMap))
		{
			m_settingsData.useDisplMap = (useDisplMap) ? 1 : 0;
		}
		ImGui::DragFloat("Displacement Weight##", &m_settingsData.displWeight, 0.1f, 0.0f, 2.0f);
		bool useSpecMap = m_settingsData.useSpecMap > 0;
		if (ImGui::Checkbox("Use Specular Map##", &useSpecMap))
		{
			m_settingsData.useSpecMap = (useSpecMap) ? 1 : 0;
		}
		bool useShadowMap = m_settingsData.useShadowMap > 0;
		if (ImGui::Checkbox("Use Shadow Map##", &useShadowMap))
		{
			m_settingsData.useShadowMap = (useShadowMap) ? 1 : 0;
		}
		ImGui::DragFloat("Depth Bias##", &m_settingsData.depthBias, 0.0000001f, 0.f, 1.f, "%.6f");
		bool useSkinning = m_settingsData.useSkinning > 0;
		if (ImGui::Checkbox("Use Skinning##", &useSkinning))
		{
			m_settingsData.useSkinning = (useSkinning) ? 1 : 0;
		}
	}
#endif
}
