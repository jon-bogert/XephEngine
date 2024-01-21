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
	_modelID = id;
	_isLooping = false;
	_animationTime = 0.f;
	_clipIndex = -1;
}

void xe::Graphics::Animator::PlayAnimation(int clipIndex, bool looping)
{
	_clipIndex = clipIndex;
	_isLooping = looping;
	_animationTime = 0.f;
}

void xe::Graphics::Animator::StartBlend(int nextIndex, float time)
{
	if (_isBlending && _blendTimer / _blendTimeTotal > 0.5f)
	{
		_clipIndex = _nextClipIndex;
	}
	_nextClipIndex = nextIndex;
	_blendTimeTotal = time;
	_invBlendTimeTotal = 1.f / time;
	_isBlending = true;
}

void xe::Graphics::Animator::SetMoveBlend(int idle, int fwd, int bkwd, int right, int left)
{
	_blendMoveMode = true;
	_blendMoveInfo.idle = idle;
	_blendMoveInfo.frwd = fwd;
	_blendMoveInfo.bkwd = bkwd;
	_blendMoveInfo.right = right;
	_blendMoveInfo.left = left;
}

void xe::Graphics::Animator::Update(const float deltaTime)
{
	if (_clipIndex < 0)
		return;

	if (_isBlending)
	{
		BlendUpdate(deltaTime);
	}

	Model* model = ModelManager::GetModel(_modelID);
	const AnimationClip& animClip = model->animationClips[_clipIndex];
	_animationTime += animClip.framesPerSecond * deltaTime;
	if (_animationTime > animClip.durationInFrames)
	{
		if (_isLooping)
		{
			while (_animationTime >= animClip.durationInFrames)
			{
				_animationTime -= animClip.durationInFrames;
			}
		}
		else
		{
			_animationTime = animClip.durationInFrames;
		}
	}
}

bool xe::Graphics::Animator::isFinished() const
{
	if (_isLooping || _clipIndex < 0)
	{
		return false;
	}

	Model* model = ModelManager::GetModel(_modelID);
	const AnimationClip& animClip = model->animationClips[_clipIndex];
	return _animationTime >= animClip.durationInFrames;
}

size_t xe::Graphics::Animator::GetAnimationCount() const
{
	Model* model = ModelManager::GetModel(_modelID);
	return model->animationClips.size();
}

xe::Math::Matrix4 xe::Graphics::Animator::GetToParentTransform(const Bone* bone) const
{
	if (_blendMoveMode)
	{
		return BlendMoveTransform(bone);
	}
	if (_clipIndex < 0)
	{
		return bone->toParentTransform;
	}

	Model* model = ModelManager::GetModel(_modelID);
	const AnimationClip& animClip = model->animationClips[_clipIndex];
	const Animation* animation = animClip.boneAnimations[bone->index].get();

	if (animation == nullptr)
	{
		return xe::Math::Matrix4::Identity;
		//return bone->toParentTransform;
	}

	Transform transform = animation->GetTransform(_animationTime);

	if (_isBlending)
	{
		const AnimationClip& nextAnimClip = model->animationClips[_nextClipIndex];
		const Animation* nextAnimation = nextAnimClip.boneAnimations[bone->index].get();

		Transform nextTransform = nextAnimation->GetTransform(_animationTime);
		
		Transform finalTransform;
		float t = _blendTimer * _invBlendTimeTotal;
		finalTransform.position = Lerp(transform.position, nextTransform.position, t);
		finalTransform.rotation = Quaternion::Slerp(transform.rotation, nextTransform.rotation, t);
		finalTransform.scale = Lerp(transform.scale, nextTransform.scale, t);

		return finalTransform.Matrix();
	}

	return transform.Matrix();
}

xe::Math::Matrix4 xe::Graphics::Animator::BlendMoveTransform(const Bone* bone) const
{
	if (_blendMoveInfo.idle < 0 ||
		_blendMoveInfo.frwd < 0 || 
		_blendMoveInfo.bkwd < 0 || 
		_blendMoveInfo.right < 0 || 
		_blendMoveInfo.left < 0)
		return bone->toParentTransform;

	//idle
	Model* model = ModelManager::GetModel(_modelID);
	const AnimationClip& idelAnimClip = model->animationClips[_blendMoveInfo.idle];
	const Animation* idleAnimation = idelAnimClip.boneAnimations[bone->index].get();
	Transform idleTransform = idleAnimation->GetTransform(_animationTime);

	Transform yTransform{};

	AnimationClip* yAnimClip = nullptr;
	//front back
	if (_blendMoveInfo.axis.y > 0)
	{
		yAnimClip = &model->animationClips[_blendMoveInfo.frwd];
	}
	else if (_blendMoveInfo.axis.y < 0)
	{
		yAnimClip = &model->animationClips[_blendMoveInfo.bkwd];
	}
	if (yAnimClip != nullptr)
	{
		const Animation* yAnimation = yAnimClip->boneAnimations[bone->index].get();
		Transform moveTransform = yAnimation->GetTransform(_animationTime);

		float t = fabsf(_blendMoveInfo.axis.x);
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
	if (_blendTimer >= _blendTimeTotal)
	{
		_isBlending = false;
		_blendTimer = 0;
		_clipIndex = _nextClipIndex;
		return false;
	}
	_blendTimer += deltaTime;

	return true;
}
