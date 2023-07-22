#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe::Input;

namespace fs = std::filesystem;

void GameState::Initialize()
{
	//create space in Normalized Device Coord (NDC) space (-1 -> 1 for x, y, z)
	//MeshPX mesh = MeshBuilder::CreateSkyboxPX(16.f, 16.f, 20.f);
	_meshesPC.push_back(MeshBuilder::CreateCubePC(1.f));
	_meshesPC.push_back(MeshBuilder::CreateRectPC(0.5f, 0.25f, 1.f));
	_meshesPC.push_back(MeshBuilder::CreatePlanePC(3, 3, 1.f));
	_meshesPC.push_back(MeshBuilder::CreateUVSpherePC(16, 16, 1.f));
	_meshesPC.push_back(MeshBuilder::CreateCylinderPC(16, 3));
	_meshesPC.push_back(MeshBuilder::CreateMonkeyPC());


	_meshesPX.push_back(MeshBuilder::CreateSkyspherePX(16, 16, 25.f));

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	if (_meshIndex >= _meshesPC.size())
	{
		_meshBuffer.Initialize(_meshesPX[_meshIndex]);
		_vertexShader.Initialize<VertexPX>(_shaderFileTex);
		_pixelShader.Initialize(_shaderFileTex);
	}
	else
	{
		_meshBuffer.Initialize(_meshesPC[_meshIndex]);
		_vertexShader.Initialize<VertexPC>(_shaderFile);
		_pixelShader.Initialize(_shaderFile);
	}


	_camera.SetPosition({ 0.f, 0.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_constantBuffer.Initialize(sizeof(Matrix4));

	
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
	if (InputSystem::GetKeyDown(Key::Up) && _meshIndex < _meshesPC.size() + _meshesPX.size() - 1)
	{
		SwitchMesh(_meshIndex + 1);
	}
	else if (InputSystem::GetKeyDown(Key::Down) && _meshIndex > 0)
	{
		SwitchMesh(_meshIndex - 1);
	}

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

void GameState::SwitchMesh(size_t index)
{
	if (index >= _meshesPC.size() + _meshesPX.size()) return;
	_pixelShader.Terminate();
	_sampler.Terminate();
	_diffuseTexture.Terminate();
	_vertexShader.Terminate();
	_meshBuffer.Terminate();

	if (index < _meshesPC.size())
	{
		_meshBuffer.Initialize(_meshesPC[index]);
		_vertexShader.Initialize<VertexPC>(_shaderFile);
		_pixelShader.Initialize(_shaderFile);
	}
	else
	{
		_meshBuffer.Initialize(_meshesPX[index - _meshesPC.size()]);
		_vertexShader.Initialize<VertexPX>(_shaderFileTex);
		_diffuseTexture.Initialize(L"../../Assets/Textures/skysphere/sky.jpg");
		_sampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
		_pixelShader.Initialize(_shaderFileTex);
	}

	_meshIndex = index;
}
