#ifndef __XE_GRAPHICS_ANIMATIONBUILDER_H__
#define __XE_GRAPHICS_ANIMATIONBUILDER_H__

#include "Animation.h"

namespace xe::Graphics
{
	class AnimationBuilder
	{
		Animation _workingCopy;

	public:
		AnimationBuilder& AddPositionKey(const xe::Math::Vector3& position, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddRotationKey(const xe::Math::Quaternion& rotation, float time, EaseType easeType = EaseType::Linear);
		AnimationBuilder& AddScaleKey(const xe::Math::Vector3& scale, float time, EaseType easeType = EaseType::Linear);

		[[nodiscard]] Animation Build();
	};
}

#endif //__XE_GRAPHICS_ANIMATIONBUILDER_H__