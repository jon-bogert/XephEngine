#include "CustomFactory.h"

#include "TypeIDs.h"

bool xe::Customs::CustomComponentMake(const std::string& compName, const yaml_val& data, GameObject& gameObject)
{
	if (compName == "NewComponent")
	{
		//NewComponent* newComponent = gameObject.AddComponent<NewComponent>();
		//newComponent->Deserialize(data);
		return true;
	}
	return false;
}

bool xe::Customs::CustomServiceMake(const std::string& serviceName, const yaml_val& data, World& gameObject)
{
	if (serviceName == "NewService")
	{
		//NewService* newService = gameObject.AddComponent<NewService>();
		//newService->Deserialize(data);
		return true;
	}
	return false;
}
