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
	PushKey(m_workingCopy.m_positionKeys, position, time, easeType);
	m_workingCopy.m_duration = xe::Math::Max(m_workingCopy.m_duration, time);
	return *this;
}

AnimationBuilder& xe::Graphics::AnimationBuilder::AddRotationKey(const xe::Math::Quaternion& rotation, float time, EaseType easeType)
{
	PushKey(m_workingCopy.m_rotationKeys, rotation, time, easeType);
	m_workingCopy.m_duration = xe::Math::Max(m_workingCopy.m_duration, time);
	return *this;
}

AnimationBuilder& xe::Graphics::AnimationBuilder::AddScaleKey(const xe::Math::Vector3& scale, float time, EaseType easeType)
{
	PushKey(m_workingCopy.m_scaleKeys, scale, time, easeType);
	m_workingCopy.m_duration = xe::Math::Max(m_workingCopy.m_duration, time);
	return *this;
}

Animation xe::Graphics::AnimationBuilder::Build()
{
	ASSERT(!m_workingCopy.m_positionKeys.empty() || !m_workingCopy.m_rotationKeys.empty() || !m_workingCopy.m_scaleKeys.empty(), "AnimationBuilder: Could not build Animation");
	return std::move(m_workingCopy);
}
