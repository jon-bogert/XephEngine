#ifndef XE_GRAPHICS_RENDEROBJECT_H
#define XE_GRAPHICS_RENDEROBJECT_H

#include "Transform.h"
#include "MeshBuffer.h"
#include "Texture.h"

namespace xe::Graphics
{
	class RenderObject
	{
	public:
		Transform transform;
		MeshBuffer meshBuffer;
		Texture diffuseTexture;

		void Terminate()
		{
			diffuseTexture.Terminate();
			meshBuffer.Terminate();
		}


	};
}

#endif //XE_GRAPHICS_RENDEROBJECT_H