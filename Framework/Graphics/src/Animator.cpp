#include "Pch.h"
#include "Animator.h"

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

void xe::Graphics::Animator::Update(const float deltaTime)
{
	if (_clipIndex < 0)
		return;

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
		return bone->toParentTransform;
	}

	Transform transform = animation->GetTransform(_animationTime);
	return transform.Matrix();
}
