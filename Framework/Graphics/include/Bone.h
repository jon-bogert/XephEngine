#ifndef __XE_GRAPHICS_BONE_H__
#define __XE_GRAPHICS_BONE_H__

#include "Common.h"

namespace xe::Graphics
{
	struct Bone
	{
		std::string name;
		int index = -1;

		Bone* parent;
		int parentIndex = -1;

		std::vector<Bone*> children;
		std::vector<int> childrenIndices;

		xe::Math::Matrix4 toParentTransform;
		xe::Math::Matrix4 offsetTransform;
	};
}

#endif //!__XE_GRAPHICS_BONE_H__
