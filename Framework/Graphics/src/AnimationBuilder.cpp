#include "Pch.h"
#include "AnimationBuilder.h"

using namespace xe::Graphics;

namespace
{
	template<class T>
	inline void PushKey(Keyframes<T>& keyframes, const T& value, float t, EaseType easeType)
	{
		ASSERT(keyframes.empty() || keyframes.back().time <= t, "AnimationBuilder: cannot add keyframe");
		keyframes.emplace_back(value, t, easeType);
	}
}

AnimationBuilder& xe::Graphics::AnimationBuilder::AddPositionKey(const xe::Math::Vector3& position, float time, EaseType easeType)
{
	PushKey(_workingCopy._positionKeys, position, time, easeType);
	_workingCopy._duration = xe::Math::Max(_workingCopy._duration, time);
	return *this;
}

AnimationBuilder& xe::Graphics::AnimationBuilder::AddRotationKey(const xe::Math::Quaternion& rotation, float time, EaseType easeType)
{
	PushKey(_workingCopy._rotationKeys, rotation, time, easeType);
	_workingCopy._duration = xe::Math::Max(_workingCopy._duration, time);
	return *this;
}

AnimationBuilder& xe::Graphics::AnimationBuilder::AddScaleKey(const xe::Math::Vector3& scale, float time, EaseType easeType)
{
	PushKey(_workingCopy._scaleKeys, scale, time, easeType);
	_workingCopy._duration = xe::Math::Max(_workingCopy._duration, time);
	return *this;
}

Animation xe::Graphics::AnimationBuilder::Build()
{
	ASSERT(!_workingCopy._positionKeys.empty() || !_workingCopy._rotationKeys.empty() || !_workingCopy._scaleKeys.empty(), "AnimationBuilder: Could not build Animation");
	return std::move(_workingCopy);
}
