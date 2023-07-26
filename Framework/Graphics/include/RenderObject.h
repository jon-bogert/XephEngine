#ifndef __XE_GRAPHICS_RENDEROBJECT_H__
#define __XE_GRAPHICS_RENDEROBJECT_H__

#include "Transform.h"
#include "MeshBuffer.h"
#include "TextureManager.h"
#include "Material.h"

namespace xe::Graphics
{
	class RenderObject
	{
	public:
		Transform transform;
		Material material;
		MeshBuffer meshBuffer;
		TextureID diffuseMapID;
		TextureID normalMapID;

		void Terminate()
		{
			meshBuffer.Terminate();
		}
	};
}

#endif //XE_GRAPHICS_RENDEROBJECT_H