#include "Pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "FPSCameraComponent.h"
#include "ModelComponent.h"
#include "MeshComponent.h"

using yaml_val = YAML::iterator::value_type;

void xe::GameObjectFactory::Make(const std::string& filePath, GameObject& gameObject)
{
	if (!std::filesystem::exists(filePath))
		ASSERT(false, "file path doesn't exist");

	YAML::Node file;
	try
	{
		file = YAML::LoadFile(filePath);
	}
	catch (std::exception e)
	{
		ASSERT(false, "Error while reading yaml file");
	}

	for (const yaml_val& component : file["components"])
	{
		std::string componentName = component["type"].as<std::string>();
		if (componentName == "TransformComponent")
		{
			TransformComponent* transformComponent = gameObject.AddComponent<TransformComponent>();
			transformComponent->Deserialize(component);
		}
		else if (componentName == "CameraComponent")
		{
			CameraComponent* cameraComponent = gameObject.AddComponent<CameraComponent>();
			cameraComponent->Deserialize(component);
		}
		else if (componentName == "FPSCameraComponent")
		{
			FPSCameraComponent* fpsCameraComponent = gameObject.AddComponent<FPSCameraComponent>();
			fpsCameraComponent->Deserialize(component);
		}
		else if (componentName == "ModelComponent")
		{
			ModelComponent* modelComponent = gameObject.AddComponent<ModelComponent>();
			modelComponent->Deserialize(component);
		}
		else if (componentName == "MeshComponent")
		{
			MeshComponent* meshComponent = gameObject.AddComponent<MeshComponent>();
			meshComponent->Deserialize(component);
		}
		else
		{
			ASSERT(false, "GameObjectFactory: undefined component type");
		}
	}
}
