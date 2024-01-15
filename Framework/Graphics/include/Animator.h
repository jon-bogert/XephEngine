#ifndef __XE_GRAPHICS_ANIMATOR_H__
#define __XE_GRAPHICS_ANIMATOR_H__

#include "ModelManager.h"
#include "Bone.h"

namespace xe::Graphics
{
	class Animator
	{
	public:
		void Initialize(ModelID id);
		void PlayAnimation(int clipIndex, bool looping);
		void StartBlend(int nextIndex, float time);
		void SetMoveBlend(int idle, int fwd, int bkwd, int right, int left);
		void SetMoveBlend(bool isOn) { m_blendMoveMode = isOn; }
		void UpdateBlendMove(xe::Math::Vector2 axis) { m_blendMoveInfo.axis = axis; }
		void Update(const float deltaTime);

		bool isFinished() const;
		size_t GetAnimationCount() const;
		xe::Math::Matrix4 GetToParentTransform(const Bone* bone) const;
		xe::Math::Matrix4 BlendMoveTransform(const Bone* bone) const;

	private:
		bool BlendUpdate(const float deltaTime);

		ModelID m_modelID;
		float m_clipIndex;
		float m_nextClipIndex;
		float m_animationTime = 0.f;
		bool m_isLooping = false;

		bool m_isBlending = false;
		float m_blendTimeTotal = 1.f;
		float m_invBlendTimeTotal = 1.f;
		float m_blendTimer = 0.f;
		bool m_blendMoveMode = false;

		struct BlendMoveInfo
		{
			xe::Math::Vector2 axis;
			int idle = -1;
			int frwd = -1;
			int bkwd = -1;
			int left = -1;
			int right = -1;
		};
		BlendMoveInfo m_blendMoveInfo;
	};
}

#endif // !__XE_GRAPHICS_ANIMATOR_H__