#ifndef __XE_GRAPHICS_ANIMATION_H__
#define __XE_GRAPHICS_ANIMATION_H__

#include "Keyframe.h"
#include "Transform.h"

namespace xe::Graphics
{
	class Animation
	{
		friend class AnimationBuilder;
		friend class AnimationIO;

		PositionKeys _positionKeys;
		RotationKeys _rotationKeys;
		ScaleKeys _scaleKeys;
		float _duration;

	public:
		Transform GetTransform(float time) const;
		float GetDuration() const;

	private:
		xe::Math::Vector3 GetPosition(float time) const;
		xe::Math::Quaternion GetRotation(float time) const;
		xe::Math::Vector3 GetScale(float time) const;
	};
}

#endif
