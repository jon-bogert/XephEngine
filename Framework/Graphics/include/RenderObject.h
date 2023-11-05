#ifndef __XE_GRAPHICS_RENDEROBJECT_H__
#define __XE_GRAPHICS_RENDEROBJECT_H__

#include "Transform.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Material.h"
#include "ModelManager.h"

namespace xe::Graphics
{
	struct Model;
	struct Skeleton;
	class Animator;
	class RenderObject
	{
	public:
		Transform transform;
		Material material;
		MeshBuffer meshBuffer;
		TextureID diffuseMapID;
		TextureID normalMapID;
		TextureID displMapID;
		TextureID specMapID;

		ModelID modelID = 0;

		const Skeleton* skeleton = nullptr;
		const Animator* animator = nullptr;

		void Terminate();
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model, const Animator* animator = nullptr);
	[[nodiscard]] RenderGroup CreateRenderGroup(ModelID modelID, const Animator* animator = nullptr);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	template<typename Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Draw(renderObject);
		}
	}
}

#endif //XE_GRAPHICS_RENDEROBJECT_H