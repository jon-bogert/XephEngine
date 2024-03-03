#include "EditorState.h"
#include "CustomFactory.h"

using namespace xe;
using namespace xe::Core;
using namespace xe::Math;

void EditorState::Initialize()
{
	GameObjectFactory::SetCustomMake(Customs::CustomComponentMake);
	World::SetCustomServiceMake(Customs::CustomServiceMake);
	m_world.LoadLevel("../../Assets/Scenes/test_level.yaml");

	PhysicsService* physics = m_world.GetService<PhysicsService>();
	if (physics != nullptr)
	{
		physics->SetEnabled(false);
	}
}

void EditorState::Terminate()
{
	PhysicsService* physics = m_world.GetService<PhysicsService>();
	if (physics != nullptr)
	{
		physics->SetEnabled(true);
	}
	m_world.Terminate();
}

void EditorState::Update(const float& deltaTime)
{
	m_world.Update(deltaTime);
	UpdateCameraControl(deltaTime);
}

void EditorState::Draw()
{
	m_world.Draw();
}

void EditorState::DebugUI()
{
	ImGui::Begin("Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	m_world.EditorUI();

	if (ImGui::Button("Save##EditorState"))
	{
		m_world.SaveLevel(m_world.GetLevelFile());
	}
	ImGui::SameLine();
	if (ImGui::Button("Exit##EditorState"))
	{
		MainApp().ChangeState("GameState");
	}
	ImGui::End();
}

void EditorState::UpdateCameraControl(const float& deltaTime)
{
	CameraService* cameraService = m_world.GetService<CameraService>();
	if (InputSystem::GetKeyDown(Key::One))
		cameraService->SetMainCamera(0);
	if (InputSystem::GetKeyDown(Key::Two))
		cameraService->SetMainCamera(1);
}