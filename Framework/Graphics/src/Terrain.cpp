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

	_rows = dimensions;
	_columns = dimensions;

	const float tileCount = 35;

	_mesh.vertices.resize(_rows * _columns);
	for (uint32_t z = 0; z < _rows; ++z)
	{
		for (uint32_t x = 0; x < _columns; ++x)
		{
			const int c = fgetc(file);
			const float height = (c / 255.f) * heightScale;
			const uint32_t index = x + (z * _columns);

			xe::Graphics::Vertex& vertex = _mesh.vertices[index];
			const float posX = static_cast<float>(x);
			const float posZ = static_cast<float>(z);
			vertex.position = { posX, height, posZ };
			vertex.normal = xe::Math::Vector3::YAxis;
			vertex.uvCoord.x = (static_cast<float>(x) / _columns) * tileCount;
			vertex.uvCoord.y = (static_cast<float>(z) / _rows) * tileCount;
		}
	}
	fclose(file);

	const uint32_t cells = (_rows - 1) * (_columns - 1);
	_mesh.indices.reserve(cells * 6);
	for (uint32_t z = 0; z < _rows - 1; ++z)
	{
		for (uint32_t x = 0; x < _columns - 1; ++x)
		{
			const uint32_t bl = x + (z * _columns);
			const uint32_t tl = x + ((z + 1) * _columns);
			const uint32_t br = (x + 1) + (z * _columns);
			const uint32_t tr = (x + 1) + ((z + 1) * _columns);

			_mesh.indices.push_back(bl);
			_mesh.indices.push_back(tl);
			_mesh.indices.push_back(tr);

			_mesh.indices.push_back(bl);
			_mesh.indices.push_back(tr);
			_mesh.indices.push_back(br);
		}
	}
}

float xe::Graphics::Terrain::GetHeight(const xe::Math::Vector3& position) const
{
	const int32_t x = static_cast<int32_t>(position.x);
	const int32_t z = static_cast<int32_t>(position.z);

	if (x < 0 || z < 0 || x + 1 >= _columns || z + 1 >= _rows)
	{
		return 0.0f;
	}

	const uint32_t bl = x + (z * _columns);
	const uint32_t tl = x + ((z + 1) * _columns);
	const uint32_t br = (x + 1) + (z * _columns);
	const uint32_t tr = (x + 1) + ((z + 1) * _columns);

	const float u = position.x - x;
	const float v = position.z - z;

	float height;
	if (u > v) // bottom right triangle
	{
		const xe::Graphics::Vertex& a = _mesh.vertices[br];
		const xe::Graphics::Vertex& b = _mesh.vertices[tr];
		const xe::Graphics::Vertex& c = _mesh.vertices[bl];
		const float deltaAB = b.position.y - a.position.y;
		const float deltaAC = c.position.y - a.position.y;
		height = a.position.y + (deltaAB * v) + (deltaAC * (1 - u));
	}
	else // top left
	{
		const xe::Graphics::Vertex& a = _mesh.vertices[tl];
		const xe::Graphics::Vertex& b = _mesh.vertices[tr];
		const xe::Graphics::Vertex& c = _mesh.vertices[bl];
		const float deltaAB = b.position.y - a.position.y;
		const float deltaAC = c.position.y - a.position.y;
		height = a.position.y + (deltaAB * u) + (deltaAC * (1 - v));
	}

	return height;
}

xe::Graphics::Mesh& xe::Graphics::Terrain::GetMesh()
{
	return _mesh;
}
