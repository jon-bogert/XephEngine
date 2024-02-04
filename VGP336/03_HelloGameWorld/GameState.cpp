#include "GameState.h"

using namespace xe;
using namespace xe::Core;
using namespace xe::Math;

void GameState::Initialize()
{
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