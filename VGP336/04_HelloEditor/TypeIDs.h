#pragma once

#include <XephEngine/include/TypeIDs.h>

enum class CustomComponentID
{
	NewComp = static_cast<uint32_t>(xe::ComponentID::Count),
};

enum class CustomServiceID
{
	NewService = static_cast<uint32_t>(xe::ServiceID::Count),
};