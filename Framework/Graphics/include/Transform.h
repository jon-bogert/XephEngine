#pragma once

#ifndef XE_GRAPHICS_TRANSFORM_H
#define XE_GRAPHICS_TRANSFORM_H

#include "Common.h"

namespace xe::Graphics
{
	struct Transform
	{
		Math::Vector3 position = Math::Vector3::Zero;
		Math::Quaternion rotation = Math::Quaternion::Identity;
		Math::Vector3 scale = Math::Vector3::One;

		Math::Matrix4 Matrix() const
		{
			return{
				Math::Matrix4::Scaling(scale) *
				Math::Matrix4::MatrixRotationQuaternion(rotation) *
				Math::Matrix4::Translation(position)
			};
		}
	};
}

#endif //XE_GRAPHICS_TRANSFORM_H
