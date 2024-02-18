#include "Pch.h"
#include "AnimatorComponent.h"

#include "GameObject.h"
#include "World.h"
#include "ModelComponent.h"
#include "UpdateService.h"

void xe::AnimatorComponent::Initialize()
{
	ModelComponent* modelComponent = GetGameObject().GetComponent<ModelComponent>();
	m_animator.Initialize(modelComponent->GetModelID());

	UpdateService* updateService = GetGameObject().GetWorld().GetService<UpdateService>();
	updateService->Register(this);
}

void xe::AnimatorComponent::Terminate()
{
	UpdateService* updateService = GetGameObject().GetWorld().GetService<UpdateService>();
	updateService->Unregister(this);
}

void xe::AnimatorComponent::Update(const float deltaTime)
{
	m_animator.Update(deltaTime);
}

void xe::AnimatorComponent::DebugUI()
{
	uint32_t animationCount = m_animator.GetAnimationCount();
	for (uint32_t i = 0; i < animationCount; ++i)
	{
		if (ImGui::Button((std::to_string(i) + " Play Animation##" + GetGameObject().GetName()).c_str()))
		{
			Play(i, true);
		}
	}
}

bool xe::AnimatorComponent::Play(int index, bool looping)
{
	m_animator.PlayAnimation(index, looping);
	return true;
}
