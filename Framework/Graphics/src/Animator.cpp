#include "Pch.h"
#include "Animator.h"

using namespace xe::Math;

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

void xe::Graphics::Animator::Update(const float deltaTime)
{
	if (_clipIndex < 0)
		return;

	if (_isBlending)
	{
		if (BlendUpdate(deltaTime))
			return;
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
		const AnimationClip& nextAnimClip = model->animationClips[_clipIndex];
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
