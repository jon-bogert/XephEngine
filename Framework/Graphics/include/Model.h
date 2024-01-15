#ifndef __XE_GRAPHICS_MODEL_H__
#define __XE_GRAPHICS_MODEL_H__

#include "MeshTypes.h"
#include "Material.h"
#include "Skeleton.h"
#include "AnimationClip.h"

namespace xe::Graphics
{
	struct Model
	{
		struct MeshData
		{
			Mesh mesh;
			uint32_t materialIndex = 0;
		};

		struct MaterialData
		{
			Material material;
			std::string diffuseMapName;
			std::string specularMapName;
			std::string displMapName;
			std::string normalMapName;
		};

		std::vector<MeshData> meshData;
		std::vector<MaterialData> materialData;
		std::unique_ptr<Skeleton> skeleton;
		std::vector<AnimationClip> animationClips;
	};
}

#endif //!__XE_GRAPHICS_MODEL_H__