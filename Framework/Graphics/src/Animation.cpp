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
	
	return _duration;
}

xe::Math::Vector3 xe::Graphics::Animation::GetPosition(float time) const
{
	for (uint32_t i = 0; i < _positionKeys.size(); ++i)
	{
		if (time < _positionKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(_positionKeys[i - 1].time, _positionKeys[i].time, time, _positionKeys[i].easeType);
				return xe::Math::Lerp(_positionKeys[i - 1].key, _positionKeys[i].key, t);
			}
			else
			{
				return _positionKeys[i].key;
			}
		}
	}
	if (!_positionKeys.empty())
	{
		return _positionKeys.back().key;
	}
	return xe::Math::Vector3::Zero;
}

xe::Math::Quaternion xe::Graphics::Animation::GetRotation(float time) const
{
	for (uint32_t i = 0; i < _rotationKeys.size(); ++i)
	{
		if (time < _rotationKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(_rotationKeys[i - 1].time, _rotationKeys[i].time, time, _rotationKeys[i].easeType);
				return xe::Math::Quaternion::Slerp(_rotationKeys[i - 1].key, _rotationKeys[i].key, t);
			}
			else
			{
				return _rotationKeys[i].key;
			}
		}
	}
	if (!_rotationKeys.empty())
	{
		return _rotationKeys.back().key;
	}
	return xe::Math::Quaternion::Identity;
}

xe::Math::Vector3 xe::Graphics::Animation::GetScale(float time) const
{
	for (uint32_t i = 0; i < _scaleKeys.size(); ++i)
	{
		if (time < _scaleKeys[i].time)
		{
			if (i > 0)
			{
				float t = GetLerpTime(_scaleKeys[i - 1].time, _scaleKeys[i].time, time, _scaleKeys[i].easeType);
				return xe::Math::Lerp(_scaleKeys[i - 1].key, _scaleKeys[i].key, t);
			}
			else
			{
				return _scaleKeys[i].key;
			}
		}
	}
	if (!_scaleKeys.empty())
	{
		return _scaleKeys.back().key;
	}
	return xe::Math::Vector3::One;
}
