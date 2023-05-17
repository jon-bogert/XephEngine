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
	MeshPX mesh = MeshBuilder::CreateSkyboxPX(16, 16, 25.f);

	fs::path shaderFile = L"../../../Assets/Shaders/Texture.fx";
	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	_camera.SetPosition({ 0.f, 0.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });
}

void GameState::Terminate()
{
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
	if (InputSystem::Get().IsKeyPressed(Key::Space))
	{
		_shapeType = (ShapeType)(((int)_shapeType + 1) % (int)ShapeType::Count);
	}
}

void GameState::Draw()
{
	switch (_shapeType)
	{
	case ShapeType::Transform:
		SimpleDraw::AddTransfrom(Matrix4::Identity);
		break;
	case ShapeType::Sphere:
		SimpleDraw::AddSphere(32, 32, 1.f, Colors::Purple);
		break;
	case ShapeType::BoxWireframe:
		SimpleDraw::AddBoxWireframe({ -1.f, -1.f, -1.f }, { 1.f, 1.f, 1.f }, Colors::Green);
		break;
	case ShapeType::BoxFilled:
		SimpleDraw::AddBoxFilled({ -1.f, -1.f, -1.f }, { 1.f, 1.f, 1.f }, Colors::Red);
		break;
	case ShapeType::Custom:
		//Add Something
		break;
	default:
		LOG("ShapeType not added");
		break;
	}

	SimpleDraw::Draw(_camera);
}

void GameState::UpdateCameraControl(const float& deltaTime)
{
	InputSystem& input = InputSystem::Get();
	const float moveSpeed = input.IsKeyDown(Key::LShift) ? 10.f : 2.f;
	const float turnSpeed = 0.1f;

	Vector3 moveAxis = Vector3::Zero;

	if (input.IsKeyDown(Key::W))
	{
		moveAxis.z = 1;
	}
	if (input.IsKeyDown(Key::S))
	{
		moveAxis.z = -1;
	}
	if (input.IsKeyDown(Key::D))
	{
		moveAxis.x = 1;
	}
	if (input.IsKeyDown(Key::A))
	{
		moveAxis.x = -1;
	}
	if (input.IsKeyDown(Key::E))
	{
		moveAxis.y = 1;
	}
	if (input.IsKeyDown(Key::Q))
	{
		moveAxis.y = -1;
	}
	if (input.IsMouseDown(MouseButton::Right))
	{
		_camera.Yaw(input.GetMouseMoveX() * turnSpeed * deltaTime);
		_camera.Pitch(input.GetMouseMoveY() * turnSpeed * deltaTime);
	}

	if (moveAxis == Vector3::Zero) return;

	moveAxis = Normalize(moveAxis) * moveSpeed * deltaTime;

	_camera.Walk(moveAxis.z);
	_camera.Strafe(moveAxis.x);
	_camera.Rise(moveAxis.y);
}
