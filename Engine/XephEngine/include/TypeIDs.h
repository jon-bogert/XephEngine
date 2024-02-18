#pragma once

#include "Common.h"

namespace xe
{
	enum class ComponentID
	{
		Null,
		Transform,
		Camera,
		FPSCamera,
		Model,
		Mesh,
		Rigidbody,
		Collider,
		SoundEffect,
		SoundBank,
		Animator,

		Count
	};

	enum class ServiceID
	{
		Null,
		Camera,
		Update,
		Render,
		Physics,

		Count
	};
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeID() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeID() const override {return StaticGetTypeID();}