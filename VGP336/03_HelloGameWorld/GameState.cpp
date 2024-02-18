#include "GameState.h"

using namespace xe;
using namespace xe::Core;
using namespace xe::Math;

namespace
{
	bool CustomComponentMake(const std::string& compName, const yaml_val& data, GameObject& gameObject)
	{
		if (compName == "NewComponent")
		{
			//NewComponent* newComponent = gameObject.AddComponent<NewComponent>();
			//newComponent->Deserialize(data);
			return true;
		}
		return false;
	}

	bool CustomServiceMake(const std::string& serviceName, const yaml_val& data, World& gameObject)
	{
		if (serviceName == "NewService")
		{
			//NewService* newService = gameObject.AddComponent<NewService>();
			//newService->Deserialize(data);
			return true;
		}
		return false;
	}
}

void GameState::Initialize()
{
	GameObjectFactory::SetCustomMake(CustomComponentMake);
	World::SetCustomServiceMake(CustomServiceMake);
	m_world.LoadLevel("../../Assets/Scenes/test_level.yaml");
}

void GameState::Terminate()
{
	m_world.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	m_world.Update(deltaTime);
	UpdateCameraControl(deltaTime);
}

void GameState::Draw()
{
	m_world.Draw();
}

void GameState::DebugUI()
{
	m_world.DebugUI();
}

void GameState::UpdateCameraControl(const float& deltaTime)
{
	CameraService* cameraService = m_world.GetService<CameraService>();
	if (InputSystem::GetKeyDown(Key::One))
		cameraService->SetMainCamera(0);
	if (InputSystem::GetKeyDown(Key::Two))
		cameraService->SetMainCamera(1);
}