#ifndef __XE_GRAPHICS_RENDEROBJECT_H__
#define __XE_GRAPHICS_RENDEROBJECT_H__

#include "Transform.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Material.h"

namespace xe::Graphics
{
	struct Model;
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

		void Terminate();
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]] RenderGroup CreateRenderGroup(const Model& model);
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