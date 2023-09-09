#ifndef __XE_GRAPHICS_TERRAIN_H__
#define __XE_GRAPHICS_TERRAIN_H__

#include "MeshTypes.h"

namespace xe::Graphics
{
	class Terrain
	{
		Mesh _mesh;
		uint32_t _rows = 0;
		uint32_t _columns = 0;

	public:
		void Initialize(const std::filesystem::path& filename, float heightScale);
		float GetHeight(const xe::Math::Vector3& position) const;
		Mesh& GetMesh();
	};
}

#endif //__XE_GRAPHICS_TERRAIN_H__