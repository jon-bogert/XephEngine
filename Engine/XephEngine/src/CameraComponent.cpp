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

void xe::CameraComponent::Serialize(YAML::Node& data)
{
	data["position"]["x"] = m_camera.GetPosition().x;
	data["position"]["y"] = m_camera.GetPosition().y;
	data["position"]["z"] = m_camera.GetPosition().z;

	//data["lookAt"]["x"] = m_camera.GetLookAt().x;
	//data["lookAt"]["y"] = m_camera.GetLookAt().y;
	//data["lookAt"]["z"] = m_camera.GetLookAt().z;
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
