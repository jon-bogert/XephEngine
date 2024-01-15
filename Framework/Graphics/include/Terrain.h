#ifndef __XE_GRAPHICS_TERRAIN_H__
#define __XE_GRAPHICS_TERRAIN_H__

#include "MeshTypes.h"

namespace xe::Graphics
{
	class Terrain
	{
	public:
		void Initialize(const std::filesystem::path& filename, float heightScale);
		float GetHeight(const xe::Math::Vector3& position) const;
		Mesh& GetMesh();

	private:
		Mesh m_mesh;
		uint32_t m_rows = 0;
		uint32_t m_columns = 0;
	};
}

#endif //!__XE_GRAPHICS_TERRAIN_H__