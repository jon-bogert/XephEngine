#include "Pch.h"
#include "Terrain.h"

void xe::Graphics::Terrain::Initialize(const std::filesystem::path& filename, float heightScale)
{
	FILE* file = nullptr;
	fopen_s(&file, filename.u8string().c_str(), "rb");

	ASSERT(file != nullptr, "Terrain: file was not found %s", filename.c_str());

	fseek(file, 0L, SEEK_END);
	const size_t fileSize = ftell(file);
	const uint32_t dimensions = static_cast<uint32_t>(sqrt(static_cast<float>(fileSize)));
	fseek(file, 0L, SEEK_SET);

	m_rows = dimensions;
	m_columns = dimensions;

	const float tileCount = 35;

	m_mesh.vertices.resize(m_rows * m_columns);
	for (uint32_t z = 0; z < m_rows; ++z)
	{
		for (uint32_t x = 0; x < m_columns; ++x)
		{
			const int c = fgetc(file);
			const float height = (c / 255.f) * heightScale;
			const uint32_t index = x + (z * m_columns);

			xe::Graphics::Vertex& vertex = m_mesh.vertices[index];
			const float posX = static_cast<float>(x);
			const float posZ = static_cast<float>(z);
			vertex.position = { posX, height, posZ };
			vertex.normal = xe::Math::Vector3::YAxis;
			vertex.uvCoord.x = (static_cast<float>(x) / m_columns) * tileCount;
			vertex.uvCoord.y = (static_cast<float>(z) / m_rows) * tileCount;
		}
	}
	fclose(file);

	const uint32_t cells = (m_rows - 1) * (m_columns - 1);
	m_mesh.indices.reserve(cells * 6);
	for (uint32_t z = 0; z < m_rows - 1; ++z)
	{
		for (uint32_t x = 0; x < m_columns - 1; ++x)
		{
			const uint32_t bl = x + (z * m_columns);
			const uint32_t tl = x + ((z + 1) * m_columns);
			const uint32_t br = (x + 1) + (z * m_columns);
			const uint32_t tr = (x + 1) + ((z + 1) * m_columns);

			m_mesh.indices.push_back(bl);
			m_mesh.indices.push_back(tl);
			m_mesh.indices.push_back(tr);

			m_mesh.indices.push_back(bl);
			m_mesh.indices.push_back(tr);
			m_mesh.indices.push_back(br);
		}
	}
}

float xe::Graphics::Terrain::GetHeight(const xe::Math::Vector3& position) const
{
	const int32_t x = static_cast<int32_t>(position.x);
	const int32_t z = static_cast<int32_t>(position.z);

	if (x < 0 || z < 0 || x + 1 >= m_columns || z + 1 >= m_rows)
	{
		return 0.0f;
	}

	const uint32_t bl = x + (z * m_columns);
	const uint32_t tl = x + ((z + 1) * m_columns);
	const uint32_t br = (x + 1) + (z * m_columns);
	const uint32_t tr = (x + 1) + ((z + 1) * m_columns);

	const float u = position.x - x;
	const float v = position.z - z;

	float height;
	if (u > v) // bottom right triangle
	{
		const xe::Graphics::Vertex& a = m_mesh.vertices[br];
		const xe::Graphics::Vertex& b = m_mesh.vertices[tr];
		const xe::Graphics::Vertex& c = m_mesh.vertices[bl];
		const float deltaAB = b.position.y - a.position.y;
		const float deltaAC = c.position.y - a.position.y;
		height = a.position.y + (deltaAB * v) + (deltaAC * (1 - u));
	}
	else // top left
	{
		const xe::Graphics::Vertex& a = m_mesh.vertices[tl];
		const xe::Graphics::Vertex& b = m_mesh.vertices[tr];
		const xe::Graphics::Vertex& c = m_mesh.vertices[bl];
		const float deltaAB = b.position.y - a.position.y;
		const float deltaAC = c.position.y - a.position.y;
		height = a.position.y + (deltaAB * u) + (deltaAC * (1 - v));
	}

	return height;
}

xe::Graphics::Mesh& xe::Graphics::Terrain::GetMesh()
{
	return m_mesh;
}
