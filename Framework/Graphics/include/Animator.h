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
		float _nextClipIndex;
		float _animationTime = 0.f;
		bool _isLooping = false;

		bool _isBlending = false;
		float _blendTimeTotal = 1.f;
		float _invBlendTimeTotal = 1.f;
		float _blendTimer = 0.f;

	public:
		void Initialize(ModelID id);
		void PlayAnimation(int clipIndex, bool looping);
		void StartBlend(int nextIndex, float time);
		void Update(const float deltaTime);

		bool isFinished() const;
		size_t GetAnimationCount() const;
		xe::Math::Matrix4 GetToParentTransform(const Bone* bone) const;

	private:
		bool BlendUpdate(const float deltaTime);
	};
}

#endif // __XE_GRAPHICS_ANIMATOR_H__