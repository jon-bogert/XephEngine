#include "Pch.h"
#include "AnimationUtil.h"
#include "Colors.h"
#include "SimpleDraw.h"

using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe::Graphics::AnimationUtil;

namespace
{
	void ComputeBoneTransformRecursive(const Bone* bone, BoneTransforms& boneTransforms)
	{
		if (bone != nullptr)
		{
			boneTransforms[bone->index] = bone->toParentTransform;
			if (bone->parent != nullptr)
			{
				boneTransforms[bone->index] = boneTransforms[bone->index] * boneTransforms[bone->parentIndex];
			}

			for (const Bone* child : bone->children)
			{
				ComputeBoneTransformRecursive(child, boneTransforms);
			}
		}
	}
}

void xe::Graphics::AnimationUtil::ComputeBoneTransform(ModelID modelID, BoneTransforms& boneTransforms)
{
	Model* model = ModelManager::GetModel(modelID);
	if (model->skeleton != nullptr)
	{
		boneTransforms.resize(model->skeleton->bones.size(), Matrix4::Identity);
		ComputeBoneTransformRecursive(model->skeleton->root, boneTransforms);
	}
}

void xe::Graphics::AnimationUtil::ApplyBoneOffsets(ModelID modelID, BoneTransforms& boneTransforms)
{
	Model* model = ModelManager::GetModel(modelID);
	if (model->skeleton != nullptr)
	{
		for (std::unique_ptr<Bone>& bone : model->skeleton->bones)
		{
			boneTransforms[bone->index] = bone->offsetTransform * boneTransforms[bone->index];
		}
	}
}

void xe::Graphics::AnimationUtil::DrawSkeleton(ModelID modelID, const BoneTransforms& boneTransforms)
{
	Model* model = ModelManager::GetModel(modelID);
	if (model->skeleton != nullptr)
	{
		for (std::unique_ptr<Bone>& bone : model->skeleton->bones)
		{
			if (bone->parent != nullptr)
			{
				Vector3 posA = GetTranslation(boneTransforms[bone->index]);
				Vector3 posB = GetTranslation(boneTransforms[bone->parentIndex]);
				SimpleDraw::AddLine(posA, posB, Colors::HotPink);
				SimpleDraw::AddSphere(posA, 5, 5, 0.01f, Colors::HotPink);
			}
		}
	}
}
