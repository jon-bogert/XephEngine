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
		bool _blendMoveMode = false;

		struct BlendMoveInfo
		{
			xe::Math::Vector2 axis;
			int idle = -1;
			int frwd = -1;
			int bkwd = -1;
			int left = -1;
			int right = -1;
		};
		BlendMoveInfo _blendMoveInfo;

	public:
		void Initialize(ModelID id);
		void PlayAnimation(int clipIndex, bool looping);
		void StartBlend(int nextIndex, float time);
		void SetMoveBlend(int idle, int fwd, int bkwd, int right, int left);
		void SetMoveBlend(bool isOn) { _blendMoveMode = isOn; }
		void UpdateBlendMove(xe::Math::Vector2 axis) { _blendMoveInfo.axis = axis; }
		void Update(const float deltaTime);

		bool isFinished() const;
		size_t GetAnimationCount() const;
		xe::Math::Matrix4 GetToParentTransform(const Bone* bone) const;
		xe::Math::Matrix4 BlendMoveTransform(const Bone* bone) const;

	private:
		bool BlendUpdate(const float deltaTime);
	};
}

#endif // __XE_GRAPHICS_ANIMATOR_H__