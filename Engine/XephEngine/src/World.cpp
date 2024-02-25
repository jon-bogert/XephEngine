#include "Pch.h"
#include "World.h"

#include "GameObjectFactory.h"
#include "CameraService.h"
#include "UpdateService.h"
#include "RenderService.h"
#include "PhysicsService.h"

#include "TransformComponent.h"
#include "RigidbodyComponent.h"

#include "XephEngine.h"

namespace
{
    CustomService tryMakeService;
}

void xe::World::SetCustomServiceMake(CustomService customService)
{
    tryMakeService = customService;
}

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
        servicePtr.reset();
    }

    m_services.clear();
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

    if (ImGui::Button("Edit##GameWorld"))
    {
        MainApp().ChangeState("EditorState");
    }
}

void xe::World::EditorUI()
{
    for (auto& servicePtr : m_services)
    {
        servicePtr->EditorUI();
    }
    for (Slot& slot : m_gameObjectSlots)
    {
        if (slot.gameObject != nullptr)
        {
            slot.gameObject->EditorUI();
        }
    }
    if (ImGui::Button("Save World##GameWorld"))
    {
        SaveLevel(m_levelPath);
    }
    ImGui::SameLine();
    if (ImGui::Button("Exit##World"))
    {
        MainApp().ChangeState("GameState");
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

void xe::World::LoadLevel(const std::string levelFile)
{
    if (!std::filesystem::exists(levelFile))
    {
        ASSERT(false, "World: Could not find level file");
    }

    m_levelPath = levelFile;
    YAML::Node levelInfo = YAML::LoadFile(levelFile);

    for (yaml_val service : levelInfo["services"])
    {
        std::string serviceName = service["name"].as<std::string>();
        if (tryMakeService(serviceName, service, *this))
        {
            continue;
        }
        else if (serviceName == "CameraService")
        {
            CameraService* cameraService = AddService<CameraService>();
            cameraService->Deserialize(service);
        }
        else if (serviceName == "UpdateService")
        {
            UpdateService* updateService = AddService<UpdateService>();
            updateService->Deserialize(service);
        }
        else if (serviceName == "RenderService")
        {
            RenderService* renderService = AddService<RenderService>();
            renderService->Deserialize(service);
        }
        else if (serviceName == "PhysicsService")
        {
            PhysicsService* physicsService = AddService<PhysicsService>();
            physicsService->Deserialize(service);
        }
        else
        {
            ASSERT(false, "World: service%s is not defined", serviceName.c_str());
        }
    }
    uint32_t capacity = levelInfo["capacity"].as<uint32_t>();
    Initialize(capacity);

    for (yaml_val gameObject : levelInfo["game-objects"])
    {
        std::string serializedFile = gameObject["file"].as<std::string>();
        GameObject* obj = CreateGameObject(serializedFile);

        if (obj != nullptr)
        {
            std::string name = gameObject["name"].as<std::string>();
            obj->SetName(name);
            if (gameObject["position"].IsDefined())
            {
                const float x = gameObject["position"]["x"].as<float>();
                const float y = gameObject["position"]["y"].as<float>();
                const float z = gameObject["position"]["z"].as<float>();

                TransformComponent* transformComponent = obj->GetComponent<TransformComponent>();
                transformComponent->position = { x, y, z };

                RigidbodyComponent* rigidbodyComponent = obj->GetComponent<RigidbodyComponent>();
                if (rigidbodyComponent != nullptr)
                {
                    rigidbodyComponent->SetPosition(transformComponent->position);
                }
            }
        }
    }
}

void xe::World::SaveLevel(const std::string levelFile)
{
}

void xe::World::SavePrefab(const std::string& prefabFile, const GameObjectHandle& handle)
{
    GameObject* obj = GetGameObject(handle);
    if (obj == nullptr)
        return;
    
    YAML::Node data;
    obj->Serialize(data);

    if (!std::filesystem::exists(prefabFile))
        std::filesystem::create_directories(prefabFile);

    std::ofstream file(prefabFile);
    file << data;

    file.close();
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
