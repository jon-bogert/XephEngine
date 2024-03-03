#pragma once
#include <XephEngine/include/XephEngine.h>

namespace xe::Customs
{
	bool CustomComponentMake(const std::string& compName, const yaml_val& data, GameObject& gameObject);

	bool CustomServiceMake(const std::string& serviceName, const yaml_val& data, World& gameObject);
}