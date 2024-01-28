#include "GameState.h"

using namespace xe;
using namespace xe::Core;
using namespace xe::Math;

void GameState::Initialize()
{
	_camera.SetPosition({ 0.f, 1.5f, -4.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	GameObjectFactory::Make("../../Assets/Serialized/test.yaml", m_gameObject);
	m_gameObject.Initialize();
}

void GameState::Terminate()
{

}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
}

void GameState::Draw()
{
	Graphics::SimpleDraw::Draw(_camera);
}

void GameState::DebugUI()
{
	m_gameObject.DebugUI();
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