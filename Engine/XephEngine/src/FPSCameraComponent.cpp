#include "Pch.h"
#include "FPSCameraComponent.h"

#include "World.h"
#include "UpdateService.h"
#include "CameraComponent.h"

using namespace xe::Math;

void xe::FPSCameraComponent::Initialize()
{
	m_cameraComponent = GetGameObject().GetComponent<CameraComponent>();

	UpdateService* updateService = GetGameObject().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraController: Update service is not available");
	updateService->Register(this);
}

void xe::FPSCameraComponent::Terminate()
{
	UpdateService* updateService = GetGameObject().GetWorld().GetService<UpdateService>();
	ASSERT(updateService != nullptr, "FPSCameraController: Update service is not available");
	updateService->Unregister(this);
}

void xe::FPSCameraComponent::Update(const float deltaTime)
{
	xe::Graphics::Camera& camera = m_cameraComponent->GetCamera();
	const float moveSpeed = InputSystem::GetKeyHold(Key::LShift) ? m_shiftSpeed : m_moveSpeed;
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
		camera.Yaw(mouseDelta.x * turnSpeed * deltaTime);
		camera.Pitch(mouseDelta.y * turnSpeed * deltaTime);
	}
	
	if (moveAxis == Vector3::Zero) return;
	
	moveAxis = Normalize(moveAxis) * moveSpeed * deltaTime;
	
	camera.Walk(moveAxis.z);
	camera.Strafe(moveAxis.x);
	camera.Rise(moveAxis.y);
}

void xe::FPSCameraComponent::Deserialize(const yaml_val& data)
{
	m_moveSpeed = data["moveSpeed"].as<float>();
	m_turnSpeed = data["turnSpeed"].as<float>();
	m_shiftSpeed = data["shiftSpeed"].as<float>();
}
