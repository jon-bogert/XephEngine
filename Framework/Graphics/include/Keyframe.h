#ifndef __XE_GRAPHICS_KEYFRAME_H__
#define __XE_GRAPHICS_KEYFRAME_H__

#include "Common.h"

namespace xe::Graphics
{
	enum class EaseType
	{
		Linear,
		EaseInQuad,
		EaseOutQuad,
		EaseInOutQuad
	};

	template <class T>
	struct Keyframe
	{
		T key;
		float time;
		EaseType easeType;

		Keyframe() = default;
		Keyframe(const T& k, float t, EaseType e = EaseType::Linear)
			:key(k), time(t), easeType(e) {}
	};

	template <class T>
	using Keyframes = std::vector<Keyframe<T>>;

	using PositionKeys = Keyframes<xe::Math::Vector3>;
	using RotationKeys = Keyframes<xe::Math::Quaternion>;
	using ScaleKeys = Keyframes<xe::Math::Vector3>;
}

#endif //__XE_GRAPHICS_KEYFRAME_H__