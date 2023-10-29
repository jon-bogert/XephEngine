#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe;

namespace stdfs = std::filesystem;

void GameState::Initialize()
{
	_camera.SetPosition({ 0.f, 1.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_directionalLight.direction = xe::Math::Normalize({ 1.f, -1.f, -1.f });

	stdfs::path path = L"../../Assets/Shaders/Standard.fx";
	_standardEffect.Initialize(path);

	_standardEffect.SetCamera(_camera);
	_standardEffect.SetDirectionalLight(_directionalLight);

	Mesh sphere = MeshBuilder::CreateUVSphere(128, 128, 1.f);

	ModelID modelID = ModelManager::LoadModel("../../Assets/Models/space-soldier/space-soldier.model");
	_characterID = modelID;
	_character = CreateRenderGroup(modelID);
	_characterAnimator.Initialize(modelID);

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(20, 20, 1.f);
	_ground.meshBuffer.Initialize(groundMesh);
	_ground.diffuseMapID = TextureManager::LoadTexture(L"misc/concrete.jpg");
	_ground.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	_ground.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	_ground.material.specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	_ground.material.power = 20.f;
}

void GameState::Terminate()
{
	_ground.Terminate();
	
	CleanupRenderGroup(_character);
	_standardEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
	_characterAnimator.Update(deltaTime);
}

void GameState::Draw()
{
	_standardEffect.Begin();
	_standardEffect.Draw(_ground);
	if (_drawSkeleton)
	{
		AnimationUtil::BoneTransforms boneTranforms;
		AnimationUtil::ComputeBoneTransform(_characterID, boneTranforms, &_characterAnimator);
		AnimationUtil::DrawSkeleton(_characterID, boneTranforms);
	}
	else
	{
		DrawRenderGroup(_standardEffect, _character);
	}
	_standardEffect.End();

	SimpleDraw::Draw(_camera);
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None);
	if (ImGui::CollapsingHeader("Lighting##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &_directionalLight.direction.x, 0.01f, -1.f, 1.f))
		{
			_directionalLight.direction = xe::Math::Normalize(_directionalLight.direction);
		}
		ImGui::NewLine();
		ImGui::ColorEdit4("Ambient##Light", &_directionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &_directionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &_directionalLight.specular.r);

	}
	ImGui::NewLine();
	ImGui::Checkbox("Draw Skeleton##", &_drawSkeleton);
	ImGui::InputInt("Animation Index", &_animIndex);
	ImGui::Checkbox("Loop Animation", &_loopAnimation);
	if (ImGui::Button("Play Animation"))
	{
		_characterAnimator.PlayAnimation(_animIndex, _loopAnimation);
	}
	_standardEffect.DebugUI();
	ImGui::End();

#endif // _DEBUG
}

void GameState::UpdateCameraControl(const float& deltaTime)
{
	const float moveSpeed = InputSystem::GetKeyHold(Key::LShift) ? 10.f : 2.f;
	const float turnSpeed = 0.1f;

	Vector3 moveAxis = Vector3::Zero;

	if (InputSystem::GetKeyHold(Key::W))
	{
		moveAxis.z = 1;
	}
	if (InputSystem::GetKeyHold(Key::S))
	{
		moveAxis.z = -1;
	}
	if (InputSystem::GetKeyHold(Key::D))
	{
		moveAxis.x = 1;
	}
	if (InputSystem::GetKeyHold(Key::A))
	{
		moveAxis.x = -1;
	}
	if (InputSystem::GetKeyHold(Key::E))
	{
		moveAxis.y = 1;
	}
	if (InputSystem::GetKeyHold(Key::Q))
	{
		moveAxis.y = -1;
	}
	if (InputSystem::GetMouseHold(Mouse::Button::Right))
	{

		Vector2 mouseDelta;
		InputSystem::GetMouseDelta(&mouseDelta.x);
		_camera.Yaw(mouseDelta.x * turnSpeed * deltaTime);
		_camera.Pitch(mouseDelta.y * turnSpeed * deltaTime);
	}

	if (moveAxis == Vector3::Zero) return;

	moveAxis = Normalize(moveAxis) * moveSpeed * deltaTime;

	_camera.Walk(moveAxis.z);
	_camera.Strafe(moveAxis.x);
	_camera.Rise(moveAxis.y);
}
