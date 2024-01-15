#ifndef __XE_GRAPHICS_ANIMATIONCLIP_H__
#define __XE_GRAPHICS_ANIMATIONCLIP_H__

#include "Animation.h"

namespace xe::Graphics
{
	class AnimationClip
	{
	public:
		std::string name;
		float durationInFrames = 0.f;
		float framesPerSecond = 0.f;

		std::vector<std::unique_ptr<Animation>> boneAnimations;
	};
}

#endif //!__XE_GRAPHICS_ANIMATIONCLIP_H__