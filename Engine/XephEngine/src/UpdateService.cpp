#include "Pch.h"
#include "UpdateService.h"

#include "Component.h"

void xe::UpdateService::Update(const float deltaTime)
{
	for (Component* comp : m_updateComponents)
	{
		comp->Update(deltaTime);
	}
	RegisterPendingUpdates();
}

void xe::UpdateService::Register(Component* component)
{
	if (m_isUpdating)
	{
		m_pendingUpdateComponents.push_back(component);
		return;
	}
	m_updateComponents.push_back(component);
}

void xe::UpdateService::Unregister(Component* component)
{
	auto iter = std::find(m_updateComponents.begin(), m_updateComponents.end(), component);
	if (iter != m_updateComponents.end())
	{
		m_updateComponents.erase(iter);
	}
	iter = std::find(m_pendingUpdateComponents.begin(), m_pendingUpdateComponents.end(), component);
	if (iter != m_pendingUpdateComponents.end())
	{
		m_pendingUpdateComponents.erase(iter);
	}
}

void xe::UpdateService::RegisterPendingUpdates()
{
	for (Component* comp : m_pendingUpdateComponents)
	{
		m_updateComponents.push_back(comp);
	}
	m_pendingUpdateComponents.clear();
}
