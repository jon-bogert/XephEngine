#ifndef __XE_GRAPHCS_SKELETON_H__
#define __XE_GRAPHCS_SKELETON_H__

#include "Bone.h"

namespace xe::Graphics
{
	struct Skeleton
	{
		Bone* root = nullptr;
		std::vector<std::unique_ptr<Bone>> bones;
	};
}

#endif //!__XE_GRAPHCS_SKELETON_H__