#ifndef XE_GRAPHICS_MESHTYPES_H
#define XE_GRAPHICS_MESHTYPES_H

#include "VertexTypes.h"

namespace xe::Graphics
{
	template<class VertexT>
	struct MeshBase
	{
		using VertexType = VertexT;
		std::vector<VertexType> vertices;
		std::vector<uint32_t> indices;
	};

	using MeshP = MeshBase<VertexP>;
	using MeshPC = MeshBase<VertexPC>;
	using MeshPX = MeshBase<VertexPX>;
	using Mesh = MeshBase<Vertex>;
}

#endif // XE_GRAPHICS_MESHTYPES_H