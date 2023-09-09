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

	_directionalLight.direction = xe::Math::Normalize({ 1.f, -1.f, 1.f });

	stdfs::path path = L"../../Assets/Shaders/Standard.fx";
	_standardEffect.Initialize(path);

	_standardEffect.SetCamera(_camera);
	_standardEffect.SetDirectionalLight(_directionalLight);
	_standardEffect.SetLightCamera(_shadowEffect.GetLightCamera());
	_standardEffect.SetShadowMap(_shadowEffect.GetDephtMap());

	_shadowEffect.Initialize();
	_shadowEffect.SetDirectionalLight(_directionalLight);

	_postProcEffect.Initialize("../../Assets/Shaders/PostProc.fx");
	_postProcEffect.SetTexture(&_baseRenderTarget);
	_postProcEffect.SetTexture(&_combineTexture, 1);

	_depthEffect.Initialize(_camera);
	_postProcEffect.SetTexture(&_depthEffect.GetDephtMap(), 2);
	_ssaoEffect.Initialize(_camera, _depthEffect.GetDephtMap());

	const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
	const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();
	_baseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	_combineTexture.Initialize(L"../../Assets/Textures/water/water_texture.jpg");

	Mesh sphere = MeshBuilder::CreateUVSphere(128, 128, 1.f);

	ModelID modelID = ModelManager::LoadModel("../../Assets/Models/space-soldier/space-soldier.model");
	_renderObjects.push_back(CreateRenderGroup(modelID));
	//for (auto& r : _renderObjects.back())
	//{
	//	r.transform.position = { 0.f, 2.f, 0.f };
	//}

	Mesh groundMesh = MeshBuilder::CreateGroundPlane(20, 20, 1.f);
	_ground.meshBuffer.Initialize(groundMesh);
	_ground.diffuseMapID = TextureManager::LoadTexture(L"misc/concrete.jpg");
	_ground.material.ambient = { 0.3f, 0.3f, 0.3f, 1.0f };
	_ground.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	_ground.material.specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	_ground.material.power = 20.f;

	_screenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());
}

void GameState::Terminate()
{
	_combineTexture.Terminate();
	_ssaoEffect.Terminate();
	_depthEffect.Terminate();
	_postProcEffect.Terminate();
	_baseRenderTarget.Terminate();
	_ground.Terminate();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
	{
		CleanupRenderGroup(*it);
	}
	_shadowEffect.Terminate();
	_standardEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	for (auto& obj : *_renderObjects.begin())
	{
		xe::Math::Quaternion::Rotate(obj.transform.rotation, 0.5f * deltaTime, xe::Math::Vector3::YAxis);
	}
	UpdateCameraControl(deltaTime);
	_shadowEffect.SetFocalPoint({ _camera.GetPosition().x, 0.f, _camera.GetPosition().z });
}

void GameState::Draw()
{
	//SimpleDraw::AddGroundPlane(10, xe::Colors::White);
	//SimpleDraw::Draw(_camera);
	_shadowEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		DrawRenderGroup(_shadowEffect, *it);
	}
	_shadowEffect.End();

	_depthEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		DrawRenderGroup(_depthEffect, *it);
	}
	_depthEffect.End();

	_baseRenderTarget.BeginDraw(GraphicsSystem::Get().GetClearColor());
	_standardEffect.Begin();
	_standardEffect.Draw(_ground);
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		DrawRenderGroup(_standardEffect, *it);
	}
	_standardEffect.End();
	_baseRenderTarget.EndDraw();

	//_ssaoEffect.Begin();
	//_ssaoEffect.Draw(_screenQuad);
	//_ssaoEffect.End();

	_postProcEffect.Begin();
	_postProcEffect.Draw(_screenQuad);
	_postProcEffect.End();
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
	_standardEffect.DebugUI();
	_shadowEffect.DebugUI();
	_postProcEffect.DebugUI();
	_depthEffect.DebugUI();
	_ssaoEffect.DebugUI();
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
