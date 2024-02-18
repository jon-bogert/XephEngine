#include "Pch.h"
#include "RenderService.h"

#include "World.h"
#include "CameraService.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "AnimatorComponent.h"

using namespace xe::Graphics;

void xe::RenderService::Initialize()
{
	m_cameraService = GetWorld().GetService<CameraService>();

	m_shadowEffect.Initialize();
	m_shadowEffect.SetDirectionalLight(m_directionalLight);

	m_standardEffect.Initialize("../../Assets/Shaders/Standard.fx");
	m_standardEffect.SetDirectionalLight(m_directionalLight);
	m_standardEffect.SetLightCamera(m_shadowEffect.GetLightCamera());
	m_standardEffect.SetShadowMap(m_shadowEffect.GetDepthMap());
}

void xe::RenderService::Terminate()
{
	m_standardEffect.Terminate();
	m_shadowEffect.Terminate();
}

void xe::RenderService::Update(const float deltaTime)
{
	m_fps = 1.f / deltaTime;
}

void xe::RenderService::Draw()
{
	const Camera& camera = m_cameraService->Main();
	m_standardEffect.SetCamera(camera);

	m_shadowEffect.Begin();
	for (Entry& entry : m_renderEntries)
	{
		for (RenderObject& renderObject : entry.renderGroup)
		{
			renderObject.transform = *entry.transformComponent;
		}
		DrawRenderGroup(m_shadowEffect, entry.renderGroup);
	}
	m_shadowEffect.End();

	m_standardEffect.Begin();
	for (const Entry& entry : m_renderEntries)
	{
		DrawRenderGroup(m_standardEffect, entry.renderGroup);
	}
	m_standardEffect.End();
}

void xe::RenderService::DebugUI()
{
	ImGui::Text("FPS: %f", m_fps);
	ImGui::Separator();
	if (ImGui::CollapsingHeader("Lighting##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &m_directionalLight.direction.x, 0.01f, -1.f, 1.f))
		{
			m_directionalLight.direction = xe::Math::Normalize(m_directionalLight.direction);
		}
		ImGui::NewLine();
		ImGui::ColorEdit4("Ambient##Light", &m_directionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &m_directionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &m_directionalLight.specular.r);

	}
	ImGui::NewLine();
	m_standardEffect.DebugUI();
	m_shadowEffect.DebugUI();
}

void xe::RenderService::Deserialize(const yaml_val& data)
{
	if (data["light-direction"].IsDefined())
	{
		float x = data["light-direction"]["x"].as<float>();
		float y = data["light-direction"]["y"].as<float>();
		float z = data["light-direction"]["z"].as<float>();
		m_directionalLight.direction = xe::Math::Normalize({ x, y, z });
	}
	if (data["ambient"].IsDefined())
	{
		const float r = data["ambient"]["r"].as<float>();
		const float g = data["ambient"]["g"].as<float>();
		const float b = data["ambient"]["b"].as<float>();
		const float a = data["ambient"]["a"].as<float>();
		m_directionalLight.ambient = { r, g, b, a };
	}
	if (data["diffuse"].IsDefined())
	{
		const float r = data["diffuse"]["r"].as<float>();
		const float g = data["diffuse"]["g"].as<float>();
		const float b = data["diffuse"]["b"].as<float>();
		const float a = data["diffuse"]["a"].as<float>();
		m_directionalLight.diffuse = { r, g, b, a };
	}
	if (data["specular"].IsDefined())
	{
		const float r = data["specular"]["r"].as<float>();
		const float g = data["specular"]["g"].as<float>();
		const float b = data["specular"]["b"].as<float>();
		const float a = data["specular"]["a"].as<float>();
		m_directionalLight.specular = { r, g, b, a };
	}
}

void xe::RenderService::Register(const ModelComponent* modelComponent)
{
	Entry& entry = m_renderEntries.emplace_back();
	const GameObject& gameObject = modelComponent->GetGameObject();
	entry.modelComponent = modelComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();

	const Animator* animator = nullptr;
	const AnimatorComponent* animatorComponent = gameObject.GetComponent<AnimatorComponent>();
	if (animatorComponent != nullptr)
	{
		animator = &animatorComponent->GetAnimator();
	}

	entry.renderGroup = CreateRenderGroup(modelComponent->GetModelID(), animator);
}

void xe::RenderService::Unregister(const ModelComponent* modelComponent)
{
	auto iter = std::find_if(
		m_renderEntries.begin(),
		m_renderEntries.end(),
		[&](const Entry& entry)
		{
			return entry.modelComponent == modelComponent;
		});

	if (iter != m_renderEntries.end())
	{
		CleanupRenderGroup(iter->renderGroup);
		m_renderEntries.erase(iter);
	}
}

void xe::RenderService::Register(const MeshComponent* meshComponent)
{
	Entry& entry = m_renderEntries.emplace_back();
	const GameObject& gameObject = meshComponent->GetGameObject();
	entry.meshComponent = meshComponent;
	entry.transformComponent = gameObject.GetComponent<TransformComponent>();
	entry.renderGroup = CreateRenderGroup(meshComponent->GetModel());
}

void xe::RenderService::Unregister(const MeshComponent* meshComponent)
{
	auto iter = std::find_if(
		m_renderEntries.begin(),
		m_renderEntries.end(),
		[&](const Entry& entry)
		{
			return entry.meshComponent == meshComponent;
		});

	if (iter != m_renderEntries.end())
	{
		CleanupRenderGroup(iter->renderGroup);
		m_renderEntries.erase(iter);
	}
}
