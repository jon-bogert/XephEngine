#ifndef __XE_GRAPHICS_MESHBUFFER_H__
#define __XE_GRAPHICS_MESHBUFFER_H__

namespace xe::Graphics
{
	class MeshBuffer final
	{
	public:
		enum class Topology {Points, Lines, Triangles};

		template<class VertexType>
		void Initialize(const std::vector<VertexType>& vertices)
		{
			Initialize(vertices.data(), static_cast<uint32_t>(sizeof(VertexType)), static_cast<uint32_t>(vertices.size()));
		}

		template<class MeshType>
		void Initialize(const MeshType& mesh)
		{
			Initialize(mesh.vertices.data(),
				static_cast<uint32_t>(sizeof(MeshType::VertexType)),
				static_cast<uint32_t>(mesh.vertices.size()),
				mesh.indices.data(),
				static_cast<uint32_t>(mesh.indices.size()));
		}

		void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount);
		void Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount);
		void Terminate();
		void SetTopology(Topology topology);
		void Update(const void* vertices, uint32_t vertexCount);
		void Draw() const;

	private:
		void CreateVertexBuffer(const void* vertices, uint32_t vertexSize, uint32_t vertexCount);
		void CreateIndexBuffer(const uint32_t* indices, uint32_t indexCount);

		ID3D11Buffer* m_vertexBuffer = nullptr;
		ID3D11Buffer* m_indexBuffer = nullptr;
		D3D11_PRIMITIVE_TOPOLOGY m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		uint32_t m_vertexSize;
		uint32_t m_vertexCount;

		uint32_t m_indexCount;
	};
}

#endif //!__XE_GRAPHICS_MESHBUFFER_H__
