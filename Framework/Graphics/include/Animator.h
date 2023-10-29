#ifndef __XE_GRAPHICS_ANIMATOR_H__
#define __XE_GRAPHICS_ANIMATOR_H__

#include "ModelManager.h"
#include "Bone.h"

namespace xe::Graphics
{
	class Animator
	{
		ModelID _modelID;
		float _clipIndex;
		float _animationTime = 0.f;
		bool _isLooping = false;

	public:
		void Initialize(ModelID id);
		void PlayAnimation(int clipIndex, bool looping);
		void Update(const float deltaTime);

		bool isFinished() const;
		size_t GetAnimationCount() const;
		xe::Math::Matrix4 GetToParentTransform(const Bone* bone) const;
	};
}

#endif // __XE_GRAPHICS_ANIMATOR_H__