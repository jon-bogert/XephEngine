#include "Pch.h"
#include "World.h"

#include "GameObjectFactory.h"

void xe::World::Initialize(uint32_t capacity)
{
    ASSERT(!m_initialized, "World: already initialized");
    for (auto& servicePtr : m_services)
    {
        servicePtr->Initialize();
    }

    m_gameObjectSlots.resize(capacity);
    m_freeSlots.resize(capacity);
    std::iota(m_freeSlots.begin(), m_freeSlots.end(), 0);

    m_initialized = true;
}

void xe::World::Terminate()
{
    ASSERT(!m_updating, "World: can't terminate while updating");
    if (!m_initialized)
    {
        return;
    }
    for (Slot& slot : m_gameObjectSlots)
    {
        if (slot.gameObject != nullptr)
        {
            slot.gameObject->Terminate();
            slot.gameObject.reset();
        }
    }
    for (auto& servicePtr : m_services)
    {
        servicePtr->Terminate();
    }

    m_initialized = false;
}

void xe::World::Update(const float deltaTime)
{
    for (auto& servicePtr : m_services)
    {
        servicePtr->Update(deltaTime);
    }
}

void xe::World::Draw()
{
    for (auto& servicePtr : m_services)
    {
        servicePtr->Draw();
    }
}

void xe::World::DebugUI()
{
    for (auto& servicePtr : m_services)
    {
        servicePtr->DebugUI();
    }
    for (Slot& slot : m_gameObjectSlots)
    {
        if (slot.gameObject != nullptr)
        {
            slot.gameObject->DebugUI();
        }
    }
}

GameObject* xe::World::CreateGameObject(const std::string& templatePath)
{
    ASSERT(m_initialized, "World: is not initialized");
    if (m_freeSlots.empty())
    {
        ASSERT(false, "World: no free slots available");
        return nullptr;
    }

    const uint32_t freeSlot = m_freeSlots.back();
    m_freeSlots.pop_back();

    Slot& slot = m_gameObjectSlots[freeSlot];
    std::unique_ptr<GameObject>& newObject = slot.gameObject;
    newObject = std::make_unique<GameObject>();

    GameObjectFactory::Make(templatePath, *newObject);

    newObject->m_world = this;
    newObject->m_handle.m_index = freeSlot;
    newObject->m_handle.m_generation = slot.generation;
    newObject->Initialize();
    return newObject.get();
}

GameObject* xe::World::GetGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
        return nullptr;

    return m_gameObjectSlots[handle.m_index].gameObject.get();
}

void xe::World::DestroyGameObject(const GameObjectHandle& handle)
{
    if (!IsValid(handle))
        return;

    Slot& slot = m_gameObjectSlots[handle.m_index];
    slot.generation++;
    m_slotsToDestroy.push_back(handle.m_index);
}

bool xe::World::IsValid(const GameObjectHandle& handle)
{
    if (handle.m_index < 0 || handle.m_index >= m_gameObjectSlots.size())
        return false;

    if (m_gameObjectSlots[handle.m_index].generation != handle.m_generation)
        return false;

    return true;
}

void xe::World::ProcessDestroyList()
{
    ASSERT(!m_updating, "World: can't destroy while updating");
    for (uint32_t index : m_slotsToDestroy)
    {
        Slot& slot = m_gameObjectSlots[index];
        GameObject* gameObject = slot.gameObject.get();
        ASSERT(!IsValid(gameObject->GetHandle()), "World: object is still alive");

        gameObject->Terminate();
        slot.gameObject.reset();
        m_freeSlots.push_back(index);
    }
    m_slotsToDestroy.clear();
}
