#include "EditPrefabState.h"
#include "CustomFactory.h"

using namespace xe;
using namespace xe::Core;
using namespace xe::Math;

void EditPrefabState::Initialize()
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

void EditPrefabState::Terminate()
{
	PhysicsService* physics = m_world.GetService<PhysicsService>();
	if (physics != nullptr)
	{
		physics->SetEnabled(true);
	}
	m_world.Terminate();
}

void EditPrefabState::Update(const float& deltaTime)
{
	m_world.Update(deltaTime);
	UpdateCameraControl(deltaTime);
}

void EditPrefabState::Draw()
{
	m_world.Draw();
}

void EditPrefabState::DebugUI()
{
	ImGui::Begin("Edit Template", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	m_world.EditorUI();
	if (ImGui::Button("Save##EditPrefab"))
	{
		GameObject* obj = m_world.GetGameObject(World::GetEditObject());
		m_world.SavePrefab(obj->GetTemplatePath(), obj->GetHandle());
	}
	ImGui::SameLine();
	if (ImGui::Button("Reload##EditPrefab"))
	{
		MainApp().ChangeState("EditPrefabState");
	}
	ImGui::SameLine();
	if (ImGui::Button("Exit##EditTemplate"))
	{
		MainApp().ChangeState("EditorState");
	}
	ImGui::End();
}

void EditPrefabState::UpdateCameraControl(const float& deltaTime)
{
	CameraService* cameraService = m_world.GetService<CameraService>();
	if (InputSystem::GetKeyDown(Key::One))
		cameraService->SetMainCamera(0);
	if (InputSystem::GetKeyDown(Key::Two))
		cameraService->SetMainCamera(1);
}