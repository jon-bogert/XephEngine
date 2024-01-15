#include "Pch.h"
#include "Animation.h"

namespace
{
	using namespace xe::Graphics;
	float GetLerpTime(float startTime, float endTime, float time, EaseType easeType)
	{
		float t = ((time - startTime) / (endTime - startTime));
		switch (easeType)
		{
		case EaseType::Linear:
			break;
		case EaseType::EaseInQuad:
			t = t * t;
			break;
		case EaseType::EaseOutQuad:
			t = t * (2.f - t);
			break;
		case EaseType::EaseInOutQuad:
			t *= 2.f;
			if (t < 1.f)
			{
				t = 0.5f * t * t;
			}
			else
			{
				t -= 1.f;
				t = -0.5f * ((t * (t - 2.f)) - 1.f);
			}
			break;
		default:
			ASSERT(false, "Animation GetLerpTime: EaseTypeNot Supported");
			break;
		}
		return t;
	}
}

xe::Graphics::Transform xe::Graphics::Animation::GetTransform(float time) const
{
	Transform transform;
	transform.position = GetPosition(time);
	transform.rotation = GetRotation(time);
	transform.scale = GetScale(time);
	return transform;
}

float xe::Graphics::Animation::GetDuration() const
{
	
	return m_duration;
}

xe::Math::Vector3 xe::Graphics::Animation::GetPosition(float time) const
{
	for (uint32_t i = 0; i < m_positionKeys.size(); ++i)
	{
		if (time < m_positionKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(m_positionKeys[i - 1].time, m_positionKeys[i].time, time, m_positionKeys[i].easeType);
				return xe::Math::Lerp(m_positionKeys[i - 1].key, m_positionKeys[i].key, t);
			}
			else
			{
				return m_positionKeys[i].key;
			}
		}
	}
	if (!m_positionKeys.empty())
	{
		return m_positionKeys.back().key;
	}
	return xe::Math::Vector3::Zero;
}

xe::Math::Quaternion xe::Graphics::Animation::GetRotation(float time) const
{
	for (uint32_t i = 0; i < m_rotationKeys.size(); ++i)
	{
		if (time < m_rotationKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(m_rotationKeys[i - 1].time, m_rotationKeys[i].time, time, m_rotationKeys[i].easeType);
				return xe::Math::Quaternion::Slerp(m_rotationKeys[i - 1].key, m_rotationKeys[i].key, t);
			}
			else
			{
				return m_rotationKeys[i].key;
			}
		}
	}
	if (!m_rotationKeys.empty())
	{
		return m_rotationKeys.back().key;
	}
	return xe::Math::Quaternion::Identity;
}

xe::Math::Vector3 xe::Graphics::Animation::GetScale(float time) const
{
	for (uint32_t i = 0; i < m_scaleKeys.size(); ++i)
	{
		if (time < m_scaleKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(m_scaleKeys[i - 1].time, m_scaleKeys[i].time, time, m_scaleKeys[i].easeType);
				return xe::Math::Lerp(m_scaleKeys[i - 1].key, m_scaleKeys[i].key, t);
			}
			else
			{
				return m_scaleKeys[i].key;
			}
		}
	}
	if (!m_scaleKeys.empty())
	{
		return m_scaleKeys.back().key;
	}
	return xe::Math::Vector3::One;
}
