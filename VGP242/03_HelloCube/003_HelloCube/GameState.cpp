#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;

namespace fs = std::filesystem;

void GameState::Initialize()
{
	//create space in Normalized Device Coord (NDC) space (-1 -> 1 for x, y, z)
	MeshPC mesh;
	mesh.vertices.push_back({ {-0.5f, 0.0f, 0.0f}, Colors::Blue });
	mesh.vertices.push_back({ {-0.5f, 0.75f, 0.0f}, Colors::Blue });
	mesh.vertices.push_back({ {0.0f, 0.75f, 0.0f}, Colors::Red });
	mesh.vertices.push_back({ {0.5f, 0.75f, 0.0f}, Colors::Blue });
	mesh.vertices.push_back({ {0.5f, 0.0f, 0.0f}, Colors::Green });

	mesh.indices = {
		0, 2, 4,
		0, 1, 2,
		2, 3, 4
	};

	fs::path shaderFile = L"../../../Assets/Shaders/DoSomething.fx";
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	_meshBuffer.Initialize(mesh);
	_vertexShader.Initialize<VertexPC>(shaderFile);
	_pixelShader.Initialize(shaderFile);
}

void GameState::Terminate()
{
	_vertices.clear();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
	_meshBuffer.Terminate();
}

void GameState::Draw()
{
	_vertexShader.Bind();
	_pixelShader.Bind();
	_meshBuffer.Draw();
}
