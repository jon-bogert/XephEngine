#include "Pch.h"
#include "CameraComponent.h"

#include "World.h"
#include "CameraService.h"

void xe::CameraComponent::Initialize()
{
	CameraService* cameraService = GetGameObject().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent: CameraService is not available");
	cameraService->Register(this);
}

void xe::CameraComponent::Terminate()
{
	CameraService* cameraService = GetGameObject().GetWorld().GetService<CameraService>();
	ASSERT(cameraService != nullptr, "CameraComponent: CameraService is not available");
	cameraService->Unregister(this);
}

void xe::CameraComponent::Deserialize(const yaml_val& data)
{
	m_camera.SetPosition({
		data["position"]["x"].as<float>(),
		data["position"]["y"].as<float>(),
		data["position"]["z"].as<float>(),
		});
	m_camera.SetLookAt({
		data["lookAt"]["x"].as<float>(),
		data["lookAt"]["y"].as<float>(),
		data["lookAt"]["z"].as<float>(),
		});
}
