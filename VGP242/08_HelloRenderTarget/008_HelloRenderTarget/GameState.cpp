#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe;

namespace fs = std::filesystem;
namespace gui = ImGui;

void GameState::Initialize()
{
	_camera.SetPosition({ 0.f, 1.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_rtCamera.SetPosition({ 1.f, 1.f, -5.f });
	_rtCamera.SetAspectRatio(1.f);

	MeshPX sphere = MeshBuilder::CreateUVSpherePX(60, 60, 1.f);

	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(sphere);
	_renderObjects.back().diffuseTexture.Initialize(L"../../../Assets/Textures/misc/basketball.jpg");
	_renderObjects.back().transform.position.y += 1.f;
	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(sphere);
	_renderObjects.back().transform.position.x += 2.f;
	_renderObjects.back().transform.position.y += 1.f;
	_renderObjects.back().diffuseTexture.Initialize(L"../../../Assets/Textures/misc/concrete.jpg");

	_simpleEffect.Initialize();
	_simpleEffect.SetCamera(_camera);

	_rtSimpleEffect.Initialize();
	_rtSimpleEffect.SetCamera(_rtCamera);
	_rtCamera.SetLookAt(_renderObjects.front().transform.position);

	constexpr uint32_t size = 512;
	_renderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	_renderTarget.Terminate();
	for (auto it = _renderObjects.begin(); it!= _renderObjects.end(); ++it)
	{
		it->Terminate();
	}
	_rtSimpleEffect.Terminate();
	_simpleEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
}

void GameState::Draw()
{
	_simpleEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
	{
		_simpleEffect.Draw(*it);
	}
	_simpleEffect.End();

	_renderTarget.BeginDraw();
	{
		_rtSimpleEffect.Begin();
		for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
		{
			_rtSimpleEffect.Draw(*it);
		}
		_rtSimpleEffect.End();
	}
	_renderTarget.EndDraw();
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	auto& first = _renderObjects.front();
	gui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);   
	Vector3 pos = first.transform.position;
	gui::Text("Position:");
	gui::SameLine();
	if (gui::DragFloat3("##Position", &pos.x, 0.1f))
	{
		first.transform.position = pos;
	}
	Quaternion rot = first.transform.rotation;
	gui::Text("Rotation:");
	gui::SameLine();
	if (gui::DragFloat4("##Rotation", &rot.x, 0.01f))
	{
		first.transform.rotation = rot;
	}
	Vector3 sca = first.transform.scale;
	gui::Text("Scale:");
	gui::SameLine();
	if (gui::DragFloat3("##Scale", &sca.x, 0.1f))
	{
		first.transform.scale = sca;
	}
	gui::Separator();
	gui::Text("RenderTarget");
	const char* targetsStr[] = { "Object 1", "Object 2" };
	if (gui::Combo("##TargetObject", &_selectedObj, targetsStr, 2))
	{
		auto it = _renderObjects.begin();
		std::advance(it, _selectedObj);
		_rtCamera.SetLookAt(it->transform.position);
	}
	gui::Image(
		_renderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0, },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	);

	gui::End();

	SimpleDraw::AddGroundPlane(10, Colors::White);
	SimpleDraw::Draw(_camera);
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
