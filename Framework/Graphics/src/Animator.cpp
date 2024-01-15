#include "Pch.h"
#include "Animator.h"
#include "XephInput/include/XephInput/InputSystem.h"

using namespace xe::Math;

namespace
{
	Vector2 MoveAxis()
	{
		Vector2 axis;
		xe::InputSystem::GetKeyAxisComposite2D(&axis.x, xe::Key::Left, xe::Key::Right, xe::Key::Down, xe::Key::Up);
		return axis;
	}
}

void xe::Graphics::Animator::Initialize(ModelID id)
{
	m_modelID = id;
	m_isLooping = false;
	m_animationTime = 0.f;
	m_clipIndex = -1;
}

void xe::Graphics::Animator::PlayAnimation(int clipIndex, bool looping)
{
	m_clipIndex = clipIndex;
	m_isLooping = looping;
	m_animationTime = 0.f;
}

void xe::Graphics::Animator::StartBlend(int nextIndex, float time)
{
	if (m_isBlending && m_blendTimer / m_blendTimeTotal > 0.5f)
	{
		m_clipIndex = m_nextClipIndex;
	}
	m_nextClipIndex = nextIndex;
	m_blendTimeTotal = time;
	m_invBlendTimeTotal = 1.f / time;
	m_isBlending = true;
}

void xe::Graphics::Animator::SetMoveBlend(int idle, int fwd, int bkwd, int right, int left)
{
	m_blendMoveMode = true;
	m_blendMoveInfo.idle = idle;
	m_blendMoveInfo.frwd = fwd;
	m_blendMoveInfo.bkwd = bkwd;
	m_blendMoveInfo.right = right;
	m_blendMoveInfo.left = left;
}

void xe::Graphics::Animator::Update(const float deltaTime)
{
	if (m_clipIndex < 0)
		return;

	if (m_isBlending)
	{
		BlendUpdate(deltaTime);
	}

	Model* model = ModelManager::GetModel(m_modelID);
	const AnimationClip& animClip = model->animationClips[m_clipIndex];
	m_animationTime += animClip.framesPerSecond * deltaTime;
	if (m_animationTime > animClip.durationInFrames)
	{
		if (m_isLooping)
		{
			while (m_animationTime >= animClip.durationInFrames)
			{
				m_animationTime -= animClip.durationInFrames;
			}
		}
		else
		{
			m_animationTime = animClip.durationInFrames;
		}
	}
}

bool xe::Graphics::Animator::isFinished() const
{
	if (m_isLooping || m_clipIndex < 0)
	{
		return false;
	}

	Model* model = ModelManager::GetModel(m_modelID);
	const AnimationClip& animClip = model->animationClips[m_clipIndex];
	return m_animationTime >= animClip.durationInFrames;
}

size_t xe::Graphics::Animator::GetAnimationCount() const
{
	Model* model = ModelManager::GetModel(m_modelID);
	return model->animationClips.size();
}

xe::Math::Matrix4 xe::Graphics::Animator::GetToParentTransform(const Bone* bone) const
{
	if (m_blendMoveMode)
	{
		return BlendMoveTransform(bone);
	}
	if (m_clipIndex < 0)
	{
		return bone->toParentTransform;
	}

	Model* model = ModelManager::GetModel(m_modelID);
	const AnimationClip& animClip = model->animationClips[m_clipIndex];
	const Animation* animation = animClip.boneAnimations[bone->index].get();

	if (animation == nullptr)
	{
		return xe::Math::Matrix4::Identity;
		//return bone->toParentTransform;
	}

	Transform transform = animation->GetTransform(m_animationTime);

	if (m_isBlending)
	{
		const AnimationClip& nextAnimClip = model->animationClips[m_nextClipIndex];
		const Animation* nextAnimation = nextAnimClip.boneAnimations[bone->index].get();

		Transform nextTransform = nextAnimation->GetTransform(m_animationTime);
		
		Transform finalTransform;
		float t = m_blendTimer * m_invBlendTimeTotal;
		finalTransform.position = Lerp(transform.position, nextTransform.position, t);
		finalTransform.rotation = Quaternion::Slerp(transform.rotation, nextTransform.rotation, t);
		finalTransform.scale = Lerp(transform.scale, nextTransform.scale, t);

		return finalTransform.Matrix();
	}

	return transform.Matrix();
}

xe::Math::Matrix4 xe::Graphics::Animator::BlendMoveTransform(const Bone* bone) const
{
	if (m_blendMoveInfo.idle < 0 ||
		m_blendMoveInfo.frwd < 0 || 
		m_blendMoveInfo.bkwd < 0 || 
		m_blendMoveInfo.right < 0 || 
		m_blendMoveInfo.left < 0)
		return bone->toParentTransform;

	//idle
	Model* model = ModelManager::GetModel(m_modelID);
	const AnimationClip& idelAnimClip = model->animationClips[m_blendMoveInfo.idle];
	const Animation* idleAnimation = idelAnimClip.boneAnimations[bone->index].get();
	Transform idleTransform = idleAnimation->GetTransform(m_animationTime);

	Transform yTransform{};

	AnimationClip* yAnimClip = nullptr;
	//front back
	if (m_blendMoveInfo.axis.y > 0)
	{
		yAnimClip = &model->animationClips[m_blendMoveInfo.frwd];
	}
	else if (m_blendMoveInfo.axis.y < 0)
	{
		yAnimClip = &model->animationClips[m_blendMoveInfo.bkwd];
	}
	if (yAnimClip != nullptr)
	{
		const Animation* yAnimation = yAnimClip->boneAnimations[bone->index].get();
		Transform moveTransform = yAnimation->GetTransform(m_animationTime);

		float t = fabsf(m_blendMoveInfo.axis.x);
		yTransform.position = Lerp(idleTransform.position, moveTransform.position, t);
		yTransform.rotation = Quaternion::Slerp(idleTransform.rotation, moveTransform.rotation, t);
		yTransform.scale = Lerp(idleTransform.scale, moveTransform.scale, t);
	}
	
	Transform finalTransform;
	if (yAnimClip == nullptr /* && xAnimClip == nullptr */)
	{
		finalTransform = idleTransform;
	}
	//else if both not null
	else //if (yAnimClip != nullptr)
	{
		finalTransform = yTransform;
	}
	//else (y is not null)

	return finalTransform.Matrix();

}

bool xe::Graphics::Animator::BlendUpdate(const float deltaTime)
{
	if (m_blendTimer >= m_blendTimeTotal)
	{
		m_isBlending = false;
		m_blendTimer = 0;
		m_clipIndex = m_nextClipIndex;
		return false;
	}
	m_blendTimer += deltaTime;

	return true;
}
