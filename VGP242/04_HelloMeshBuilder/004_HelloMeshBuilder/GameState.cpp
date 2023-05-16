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
	//MeshPX mesh = MeshBuilder::CreateSkyboxPX(16.f, 16.f, 20.f);
	MeshPC mesh = MeshBuilder::CreateMonkeyPC();

	fs::path shaderFile = L"../../../Assets/Shaders/DoTransform.fx";
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	_meshBuffer.Initialize(mesh);
	_vertexShader.Initialize<VertexPC>(shaderFile);
	_pixelShader.Initialize(shaderFile);

	_camera.SetPosition({ 0.f, 0.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_constantBuffer.Initialize(sizeof(Matrix4));

	_diffuseTexture.Initialize(L"../../../Assets/Textures/skysphere/sky.jpg");
	_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GameState::Terminate()
{
	_sampler.Terminate();
	_diffuseTexture.Terminate();
	_constantBuffer.Terminate();
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
	_diffuseTexture.BindPixelShader(0);
	_sampler.BindPixelShader(0);

	Matrix4 matWorld = Matrix4::RotationY(yRotation) * Matrix4::Translation(position);
	Matrix4 matView = _camera.GetViewMatrix();
	Matrix4 matProj = _camera.GetProjectionMatrix();
	Matrix4 matFinal = matWorld * matView * matProj;
	Matrix4 wvp = Transpose(matFinal);

	_constantBuffer.Update(&wvp);
	_constantBuffer.BindVertexShader(0);

	_meshBuffer.Draw();
}
