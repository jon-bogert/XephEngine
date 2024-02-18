#include "Pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ColliderComponent.h"
#include "FPSCameraComponent.h"
#include "ModelComponent.h"
#include "MeshComponent.h"
#include "RigidbodyComponent.h"
#include "SoundEffectComponent.h"
#include "SoundBankComponent.h"
#include "AnimatorComponent.h"

using yaml_val = YAML::iterator::value_type;

namespace
{
	CustomMake tryMake;
}

void xe::GameObjectFactory::SetCustomMake(CustomMake customMake)
{
	tryMake = customMake;
}

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
		if (tryMake(componentName.c_str(), component, gameObject)) // Custom Type
		{
			continue;
		}
		else if (componentName == "TransformComponent")
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
		else if (componentName == "RigidbodyComponent")
		{
			RigidbodyComponent* rigidbodyComponent = gameObject.AddComponent<RigidbodyComponent>();
			rigidbodyComponent->Deserialize(component);
		}
		else if (componentName == "ColliderComponent")
		{
			ColliderComponent* colliderComponent = gameObject.AddComponent<ColliderComponent>();
			colliderComponent->Deserialize(component);
		}
		else if (componentName == "SoundEffectComponent")
		{
			SoundEffectComponent* soundEffectComponent = gameObject.AddComponent<SoundEffectComponent>();
			soundEffectComponent->Deserialize(component);
		}
		else if (componentName == "SoundBankComponent")
		{
			SoundBankComponent* soundBankComponent = gameObject.AddComponent<SoundBankComponent>();
			soundBankComponent->Deserialize(component);
		}
		else if (componentName == "AnimatorComponent")
		{
			AnimatorComponent* animatorComponent = gameObject.AddComponent<AnimatorComponent>();
			animatorComponent->Deserialize(component);
		}
		else
		{
			ASSERT(false, "GameObjectFactory: undefined component type");
		}
	}
}
