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
	MeshPC mesh = MeshBuilder::CreateCylinderPC(8.f, 3.f);

	fs::path shaderFile = L"../../../Assets/Shaders/DoTransform.fx";
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	_meshBuffer.Initialize(mesh);
	_vertexShader.Initialize<VertexPC>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_camera.SetPosition({ 0.f, 1.f, -3.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_constantBuffer.Initialize(sizeof(Matrix4));
}

void GameState::Terminate()
{
	_constantBuffer.Terminate();
	_vertices.clear();
	_pixelShader.Terminate();
	_vertexShader.Terminate();
	_meshBuffer.Terminate();
}
float totalTime = 0.f;
Vector3 position(0.f);
float yRotation = 0.f;
void GameState::Update(const float& deltaTime)
{
	totalTime += deltaTime;
	yRotation += 0.5f * deltaTime;
	position.y = std::sin(totalTime);
}

void GameState::Draw()
{
	_vertexShader.Bind();
	_pixelShader.Bind();

	Matrix4 matWorld = Matrix4::RotationY(yRotation) * Matrix4::Translation(position);
	Matrix4 matView = _camera.GetViewMatrix();
	Matrix4 matProj = _camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	_constantBuffer.Update(&wvp);
	_constantBuffer.BindVertexShader(0);

	_meshBuffer.Draw();
}
