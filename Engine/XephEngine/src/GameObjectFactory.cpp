#include "Pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

#include "TransformComponent.h"

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
		else
		{
			ASSERT(false, "GameObjectFactory: undefined component type");
		}
	}
}
