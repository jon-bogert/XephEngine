#include "Pch.h"
#include "GameObject.h"
#include "TransformComponent.h"

#include "World.h"
#include "XephEngine.h"

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

void xe::GameObject::EditorUI()
{
	if (ImGui::CollapsingHeader(m_name.c_str()))
	{
		for (std::unique_ptr<Component>& component : m_components)
		{
			component->EditorUI();
		}
	}

	if (ImGui::Button(("Edit##" + m_name).c_str()))
	{
		//global data to load the prefab
		World::SetEditObject(m_name);
		MainApp().ChangeState("EditPrefabState");
	}
}

void xe::GameObject::Serialize(YAML::Node& data)
{
	YAML::Node components;
	for (auto& componentPtr : m_components)
	{
		YAML::Node compData;
		componentPtr->Serialize(compData);
		components.push_back(compData);
	}
	data["components"] = components;
}
