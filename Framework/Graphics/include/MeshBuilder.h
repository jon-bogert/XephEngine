#ifndef XE_GRAPHICS_MESHBUILDER_H
#define XE_GRAPHICS_MESHBUILDER_H

#include "MeshTypes.h"

namespace xe::Graphics
{
	class MeshBuilder
	{
	public:
		//Cubes
		static MeshPC CreateCubePC(float size);
		static MeshPC CreateCubePC(float size, const Color& color);

		//Rectangles
		static MeshPC CreateRectPC(float width, float height, float length);
		static MeshPC CreateRectPC(float width, float height, float length, const Color& color);

		//Plane
		static MeshPC CreatePlanePC(uint32_t numRows, uint32_t numCols, float cellSize);
		static MeshPC CreatePlanePC(uint32_t numRows, uint32_t numCols, float cellSize, const Color& color);

		//Cylinder
		static MeshPC CreateCylinderPC(uint32_t slices, uint32_t rings);

		//Sphere
		static MeshPC CreateUVSpherePC(uint32_t slices, uint32_t rings, float radius);
		static MeshPX CreateUVSpherePX(uint32_t slices, uint32_t rings, float radius);

		//Pyramid
		static MeshPC CreatePyramidPC(uint32_t size);
		static MeshPC CreatePyramidPC(uint32_t size, const Color& color);

		//Skybox
		static MeshPX CreateSkyspherePX(uint32_t slices, uint32_t rings, float radius);

		//Monkey
		static MeshPC CreateMonkeyPC();
	};
}

#endif
