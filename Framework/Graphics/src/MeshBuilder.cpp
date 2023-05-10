#include "Pch.h"
#include "MeshBuilder.h"

using namespace xe;
using namespace xe::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::Coral,
			Colors::LimeGreen,
			Colors::DeepPink,
			Colors::Red,
			Colors::DarkCyan,
			Colors::Yellow,
			Colors::Orange,
			Colors::ForestGreen
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			//front
			0, 1, 2,
			0, 2, 3,
			//right
			3, 2, 6,
			3, 6, 7,
			//back
			7, 6, 5,
			7, 5, 4,
			//left
			0, 5, 1,
			0, 4, 5,
			//top
			1, 5, 6,
			1, 6, 2,
			//bottom
			0, 3, 7,
			0, 7, 4
		};
	}

	void CreatePlaneIndices(std::vector<uint32_t>& indices, uint32_t numRows, uint32_t numCols)
	{
		for (uint32_t row = 0; row < numRows; ++row)
		{
			for (uint32_t col = 0; col < numCols; ++col)
			{
				uint32_t i = (row * (numCols + 1)) + col;

				//triangle 1
				indices.push_back(i);
				indices.push_back(i + numCols + 2);
				indices.push_back(i + 1);
				//triangle 2
				indices.push_back(i);
				indices.push_back(i + numCols + 1);
				indices.push_back(i + numCols + 2);
			}
		}
	}

	void CreateCapIndices(std::vector<uint32_t>& indices, uint32_t slices, uint32_t topIndex, uint32_t bottomIndex)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			//bottom triangle
			indices.push_back(bottomIndex);
			indices.push_back(s);
			indices.push_back(s + 1);
			//top triangle
			uint32_t topRowIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowIndex + 1);
			indices.push_back(topRowIndex);
		}
	}
}

MeshPC xe::Graphics::MeshBuilder::CreateCubePC(float size)
{
	MeshPC mesh;
	const float half = size * 0.5f;

	int index = 0;
	// front
	mesh.vertices.push_back({ { -half, -half, -half }, GetNextColor(index) });
	mesh.vertices.push_back({ { -half,  half, -half }, GetNextColor(index) });
	mesh.vertices.push_back({ {  half,  half, -half }, GetNextColor(index) });
	mesh.vertices.push_back({ {  half, -half, -half }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -half, -half,  half }, GetNextColor(index) });
	mesh.vertices.push_back({ { -half,  half,  half }, GetNextColor(index) });
	mesh.vertices.push_back({ {  half,  half,  half }, GetNextColor(index) });
	mesh.vertices.push_back({ {  half, -half,  half }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreateCubePC(float size, const Color& color)
{
	MeshPC mesh;
	const float half = size * 0.5f;

	// front
	mesh.vertices.push_back({ { -half, -half, -half }, color });
	mesh.vertices.push_back({ { -half,  half, -half }, color });
	mesh.vertices.push_back({ {  half,  half, -half }, color });
	mesh.vertices.push_back({ {  half, -half, -half }, color });
	// back
	mesh.vertices.push_back({ { -half, -half,  half }, color });
	mesh.vertices.push_back({ { -half,  half,  half }, color });
	mesh.vertices.push_back({ {  half,  half,  half }, color });
	mesh.vertices.push_back({ {  half, -half,  half }, color });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreateRectPC(float width, float height, float length)
{
	MeshPC mesh;
	const float halfWidth = width * 0.5f;
	const float halfHeight = height * 0.5f;
	const float halfLength = length * 0.5f;

	int index = 0;
	// front
	mesh.vertices.push_back({ { -halfWidth, -halfHeight, -halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ { -halfWidth,  halfHeight, -halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ {  halfWidth,  halfHeight, -halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ {  halfWidth, -halfHeight, -halfLength }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -halfWidth, -halfHeight,  halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ { -halfWidth,  halfHeight,  halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ {  halfWidth,  halfHeight,  halfLength }, GetNextColor(index) });
	mesh.vertices.push_back({ {  halfWidth, -halfHeight,  halfLength }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreateRectPC(float width, float height, float length, const Color& color)
{
	MeshPC mesh;
	const float halfWidth = width * 0.5f;
	const float halfHeight = height * 0.5f;
	const float halfLength = length * 0.5f;

	// front
	mesh.vertices.push_back({ { -halfWidth, -halfHeight, -halfLength }, color });
	mesh.vertices.push_back({ { -halfWidth,  halfHeight, -halfLength }, color });
	mesh.vertices.push_back({ {  halfWidth,  halfHeight, -halfLength }, color });
	mesh.vertices.push_back({ {  halfWidth, -halfHeight, -halfLength }, color });
	// back
	mesh.vertices.push_back({ { -halfWidth, -halfHeight,  halfLength }, color });
	mesh.vertices.push_back({ { -halfWidth,  halfHeight,  halfLength }, color });
	mesh.vertices.push_back({ {  halfWidth,  halfHeight,  halfLength }, color });
	mesh.vertices.push_back({ {  halfWidth, -halfHeight,  halfLength }, color });

	CreateCubeIndices(mesh.indices);
	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreatePlanePC(uint32_t numRows, uint32_t numCols, float cellSize)
{
	MeshPC mesh;
	const float halfWidth = static_cast<float>(numCols) * cellSize * 0.5f;
	const float halfHeight = static_cast<float>(numRows) * cellSize * 0.5f;

	float x = -halfWidth;
	float y = -halfHeight;

	int index = 0;
	for (uint32_t row = 0; row <= numRows; ++row)
	{
		for (uint32_t col = 0; col <= numCols; ++col)
		{
			mesh.vertices.push_back({ {x, y, 0.f}, GetNextColor(index) });
			x += cellSize;
		}
		x = -halfWidth;
		y += cellSize;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreatePlanePC(uint32_t numRows, uint32_t numCols, float cellSize, const Color& color)
{
	MeshPC mesh;
	const float halfWidth = static_cast<float>(numCols) * cellSize * 0.5f;
	const float halfHeight = static_cast<float>(numRows) * cellSize * 0.5f;

	float x = -halfWidth;
	float y = -halfHeight;

	for (uint32_t row = 0; row <= numRows; ++row)
	{
		for (uint32_t col = 0; col <= numCols; ++col)
		{
			mesh.vertices.push_back({ {x, y, 0.f}, color});
			x += cellSize;
		}
		x = -halfWidth;
		y += cellSize;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreateCylinderPC(uint32_t slices, uint32_t rings)
{
	MeshPC mesh;
	const float halfHeight = static_cast<float>(rings) * 0.5f;

	int index = 0;

	for (uint32_t ring = 0; ring <= rings; ++ring)
	{
		float rPos = static_cast<float>(ring);
		for (uint32_t slice = 0; slice <= slices; ++slice)
		{
			Color color = GetNextColor(index);
			float sPos = static_cast<float>(slice);
			float rotation = (sPos / static_cast<float>(slices)) * Math::Const::TwoPi;

			mesh.vertices.push_back({ {
					std::cos(rotation),
					rPos - halfHeight,
					std::sin(rotation)},
				color
			});
		}
	}

	mesh.vertices.push_back({ {0.f, halfHeight, 0.f}, GetNextColor(index) });
	mesh.vertices.push_back({ {0.f, -halfHeight, 0.f}, GetNextColor(index) });

	CreatePlaneIndices(mesh.indices, rings, slices);
	CreateCapIndices(mesh.indices, slices, mesh.vertices.size() - 2, mesh.vertices.size() - 1);

	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreateUVSpherePC(uint32_t slices, uint32_t rings, float radius)
{
	MeshPC mesh;
	const float halfHeight = static_cast<float>(rings) * 0.5f;

	int index = 0;
	float vertRotation = (Math::Const::Pi / static_cast<float>(rings - 1));
	float horizRotation = (Math::Const::TwoPi / static_cast<float>(slices));

	for (uint32_t ring = 0; ring <= rings; ++ring)
	{
		float rPos = static_cast<float>(ring);
		float phi = rPos * vertRotation;
		for (uint32_t slice = 0; slice <= slices; ++slice)
		{
			Color color = GetNextColor(index);
			float sPos = static_cast<float>(slice);
			float rotation = sPos * horizRotation;

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)},
				color
				});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX xe::Graphics::MeshBuilder::CreateUVSpherePX(uint32_t slices, uint32_t rings, float radius)
{
	MeshPX mesh;
	const float halfHeight = static_cast<float>(rings) * 0.5f;

	float vertRotation = (Math::Const::Pi / static_cast<float>(rings - 1));
	float horizRotation = (Math::Const::TwoPi / static_cast<float>(slices));
	float uStep = 1.f / static_cast<float>(slices);
	float vStep = 1.f / static_cast<float>(rings);

	for (uint32_t ring = 0; ring <= rings; ++ring)
	{
		float rPos = static_cast<float>(ring);
		float phi = rPos * vertRotation;
		for (uint32_t slice = 0; slice <= slices; ++slice)
		{
			float sPos = static_cast<float>(slice);
			float rotation = sPos * horizRotation;

			float u = 1.f - (uStep * sPos);
			float v = (vStep * rPos);

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)},
				{u, v}
				});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreatePyramidPC(uint32_t size)
{
	MeshPC mesh;
	const float half = size * 0.5f;

	int index = 0;
	// front
	mesh.vertices.push_back({ { -half, -half, -half }, GetNextColor(index)});
	mesh.vertices.push_back({ { 0.f,  half, 0.f }, GetNextColor(index) });
	mesh.vertices.push_back({ {  half, -half, -half }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -half, -half,  half }, GetNextColor(index) });
	mesh.vertices.push_back({ { half, -half,  half }, GetNextColor(index) });

	mesh.indices = {
		//front
		0, 1, 2,
		//right
		2, 1, 4,
		//back
		4, 1, 3,
		//left
		0, 3, 1,
		//bottom
		0, 2, 4,
		0, 4, 3
	};
	return mesh;
}

MeshPC xe::Graphics::MeshBuilder::CreatePyramidPC(uint32_t size, const Color& color)
{
	MeshPC mesh;
	const float half = size * 0.5f;

	// front
	mesh.vertices.push_back({ { -half, -half, -half }, color });
	mesh.vertices.push_back({ { 0.f,  half, 0.f }, color });
	mesh.vertices.push_back({ {  half, -half, -half }, color });
	// back
	mesh.vertices.push_back({ { -half, -half,  half }, color });
	mesh.vertices.push_back({ { half, -half,  half }, color });

	mesh.indices = {
		//front
		0, 1, 2,
		//right
		2, 1, 4,
		//back
		4, 1, 3,
		//left
		0, 3, 1,
		//bottom
		0, 2, 4,
		0, 4, 3
	};
	return mesh;
}

MeshPX xe::Graphics::MeshBuilder::CreateSkyboxPX(uint32_t slices, uint32_t rings, float radius)
{
	MeshPX mesh;
	const float halfHeight = static_cast<float>(rings) * 0.5f;

	float vertRotation = (Math::Const::Pi / static_cast<float>(rings - 1));
	float horizRotation = (Math::Const::TwoPi / static_cast<float>(slices));
	float uStep = 1.f / static_cast<float>(slices);
	float vStep = 1.f / static_cast<float>(rings);

	for (uint32_t ring = 0; ring <= rings; ++ring)
	{
		float rPos = static_cast<float>(ring);
		float phi = rPos * vertRotation;
		for (uint32_t slice = 0; slice <= slices; ++slice)
		{
			float sPos = static_cast<float>(slice);
			float rotation = sPos * horizRotation;

			float u = 1.f - (uStep * sPos);
			float v = (vStep * rPos);

			mesh.vertices.push_back({ {
					radius * cos(rotation) * sin(phi),
					radius * cos(phi),
					radius * sin(rotation) * sin(phi)},
				{u, v}
			});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}
