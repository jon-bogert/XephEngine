#ifndef __XE_GRAPHICS_WATER_H__
#define __XE_GRAPHICS_WATER_H__

#include "MeshTypes.h"

namespace xe::Graphics
{
	class Water
	{
	public:
		void Initialize(const Mesh& mesh);
		Mesh& GetMesh();

	private:
		Mesh m_mesh;
		uint32_t m_rows = 0;
		uint32_t m_columns = 0;
	};
}
#endif //!__XE_GRAPHICS_WATER_H__