#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe::Input;

namespace fs = std::filesystem;
namespace gui = ImGui;

void GameState::Initialize()
{
	MeshPX mesh = MeshBuilder::CreateSkyspherePX(16, 16, 25.f);

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
		SimpleDraw::AddTransfrom(Matrix4::Identity.Translation(_transfPosition));
		break;
	case ShapeType::Sphere:
		SimpleDraw::AddSphere(32, 32, _sphereRadius, _shapeColor);
		break;
	case ShapeType::BoxWireframe:
		SimpleDraw::AddBoxWireframe({ -1.f, -1.f, -1.f }, { 1.f, 1.f, 1.f }, _shapeColor);
		break;
	case ShapeType::BoxFilled:
		SimpleDraw::AddBoxFilled({-1.f, -1.f, -1.f}, { 1.f, 1.f, 1.f }, _shapeColor);
		break;
	case ShapeType::Custom:
		SimpleDraw::AddTransfrom(Matrix4::Identity.Translation(_transfPosition));
		SimpleDraw::AddBoxFilled({ 0.95f, -0.05f, -0.05f }, { 1.05f, 0.05f, 0.05f }, Colors::Red); // X
		SimpleDraw::AddBoxFilled({ -0.05f, 0.95f, -0.05f }, { 0.05f, 1.05f, 0.05f }, Colors::Green); // Y
		SimpleDraw::AddBoxFilled({ -0.05f, -0.05f, 0.95f }, { 0.05f, 0.05f, 1.05f }, Colors::Blue); // Z
		break;
	default:
		LOG("ShapeType not added");
		break;
	}

	SimpleDraw::Draw(_camera);
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	gui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	int currItem = (int)_shapeType;
	const char* shapeItemsStr[] = {
		"Transform",
		"Sphere",
		"Box Wireframe",
		"Box Filled",
		"Custom"
	};
	gui::Text("Shape Type");
	gui::SameLine();
	if (gui::Combo("##ShapeType", &currItem, shapeItemsStr, (int)ShapeType::Count))
	{
		_shapeType = (ShapeType)currItem;
	}
	if (_shapeType != ShapeType::Transform && _shapeType != ShapeType::Custom)
	{
		gui::Text("Use Transparency:");
		gui::SameLine();
		gui::Checkbox("##UseTrasparency", &_useTransp);
		if (_useTransp)
		{
			gui::ColorEdit4("##ShapeColor", &_shapeColor.r);
		}
		else
		{
			gui::ColorEdit3("##ShapeColor", &_shapeColor.r);
			_shapeColor.a = 1.f;
		}
	}
	else if (_shapeType == ShapeType::Transform)
	{
		gui::Text("Position:");
		gui::SameLine();
		gui::DragFloat3("##ShapePosition", &_transfPosition.x, 0.01f, -10.f, 10.f);
	}

	if (_shapeType == ShapeType::Sphere)
	{
		gui::DragFloat("##SphereRadius", &_sphereRadius, 0.1f, 0.5f, 10.0f);
	}
	else
	{
		_sphereRadius = 1.f;
	}

	gui::End();
#endif // _DEBUG
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
