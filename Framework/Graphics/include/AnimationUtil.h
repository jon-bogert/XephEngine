#ifndef __XE_GAPHICS_ANIMATIONUTIL_H__
#define __XE_GAPHICS_ANIMATIONUTIL_H__

#include "ModelManager.h"
#include "Animator.h"

namespace xe::Graphics::AnimationUtil
{
	using BoneTransforms = std::vector<xe::Math::Matrix4>;

	void ComputeBoneTransform(ModelID modelID, BoneTransforms& boneTransforms, const Animator* animator = nullptr);
	void ApplyBoneOffsets(ModelID modelID, BoneTransforms& boneTransforms);
	void DrawSkeleton(ModelID modelID, const BoneTransforms& boneTransforms);
}

#endif