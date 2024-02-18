#include "Pch.h"
#include "GameObject.h"
#include "TransformComponent.h"

static uint32_t s_guid = 0;

void xe::GameObject::Initialize()
{
	ASSERT(!m_initialized, "GameObject is already initialized");

	for (std::unique_ptr<Component>& component : m_components)
	{
		component->Initialize();
	}
	m_initialized = true;
	m_guid = ++s_guid;

	ASSERT(HasComponent<TransformComponent>(), "GameObject must contain transform components");
}

void xe::GameObject::Terminate()
{
	for (std::unique_ptr<Component>& component : m_components)
	{
		component->Terminate();
	}
}

void xe::GameObject::DebugUI()
{
	if (ImGui::CollapsingHeader(m_name.c_str()))
	{
		for (std::unique_ptr<Component>& component : m_components)
		{
			component->DebugUI();
		}
	}
}
