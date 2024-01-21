#ifndef __SE_GRAPHICS_WATER_H__
#define __SE_GRAPHICS_WATER_H__

#include "MeshTypes.h"

namespace xe::Graphics
{
	class Water
	{
		Mesh _mesh;
		uint32_t _rows = 0;
		uint32_t _columns = 0;

	public:
		void Initialize(const Mesh& mesh);
		Mesh& GetMesh();
	};
}
#endif // __SE_GRAPHICS_WATER_H__