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
	_celEffect.Initialize(path);

	_celEffect.SetCamera(_camera);
	_celEffect.SetDirectionalLight(_directionalLight);

	Mesh sphere = MeshBuilder::CreateUVSphere(128, 128, 1.f);

	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(sphere);
	_renderObjects.back().diffuseMapID = TextureManager::LoadTexture("earth.jpg");
	_renderObjects.back().normalMapID = TextureManager::LoadTexture("earth_normal.jpg");
	_renderObjects.back().displMapID = TextureManager::LoadTexture("earth_bump.jpg");
	_renderObjects.back().specMapID = TextureManager::LoadTexture("earth_spec.jpg");
	_renderObjects.back().transform.position.y += 1.f;

	const uint32_t size = 512;
	_renderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	_renderTarget.Terminate();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
	{
		it->Terminate();
	}
	_celEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
}

void GameState::Draw()
{
	_camera.SetAspectRatio(1.f);
	_renderTarget.BeginDraw();
	_celEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		_celEffect.Draw(*it);
	}
	_celEffect.End();
	_renderTarget.EndDraw();

	_camera.SetAspectRatio(0.f);
	_celEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); it++)
	{
		_celEffect.Draw(*it);
	}
	_celEffect.End();
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
	int i = 0;
	for (auto& it : _renderObjects)
	{
		if (ImGui::CollapsingHeader("Material##" + i, ImGuiTreeNodeFlags_DefaultOpen))
		{
			ImGui::ColorEdit4("Ambient##Material", &it.material.ambient.r);
			ImGui::ColorEdit4("Diffuse##Material", &it.material.diffuse.r);
			ImGui::ColorEdit4("Specular##Material", &it.material.specular.r);
			ImGui::DragFloat("Specular Intensity##Material" + i, &it.material.power);
			ImGui::DragFloat("Normal Map Intensity##Material" + i, &it.material.normalMapIntensity, 0.01, 0.f, 1.f);
		}
		++i;
	}
	ImGui::NewLine();
	ImGui::Image(
		_renderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	);
	_celEffect.DebugUI();
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
