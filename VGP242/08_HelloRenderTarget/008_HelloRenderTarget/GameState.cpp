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
	_camera.SetPosition({ 0.f, 1.f, -5.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	MeshPX sphere = MeshBuilder::CreateUVSpherePX(60, 60, 1.f);

	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(sphere);
	_renderObjects.back().diffuseTexture.Initialize(L"../../../Assets/Textures/misc/basketball.jpg");
	_renderObjects.back().transform.position.y += 1.f;
	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(sphere);
	_renderObjects.back().transform.position.x += 2.f;
	_renderObjects.back().transform.position.y += 1.f;
	_renderObjects.back().diffuseTexture.Initialize(L"../../../Assets/Textures/misc/concrete.jpg");

	_simpleEffect.Initialize();
	_simpleEffect.SetCamera(_camera);

	constexpr uint32_t size = 512;
	_renderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	_renderTarget.Terminate();
	for (size_t i = 0; i < _renderObjects.size(); ++i)
	{
		_renderObjects[i].Terminate();
	}
	_simpleEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
}

void GameState::Draw()
{
	_simpleEffect.Begin();
	for (size_t i = 0; i < _renderObjects.size(); ++i)
	{
		_simpleEffect.Draw(_renderObjects[i]);
	}
	_simpleEffect.End();

	float origRatio = _camera.GetAspectRatio();
	_camera.SetAspectRatio(1.f);
	_renderTarget.BeginDraw();
	{
		_simpleEffect.Begin();
		for (size_t i = 0; i < _renderObjects.size(); ++i)
		{
			_simpleEffect.Draw(_renderObjects[i]);
		}
		_simpleEffect.End();
	}
	_renderTarget.EndDraw();
	_camera.SetAspectRatio(origRatio);
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	gui::Begin("DebugUI", nullptr, ImGuiWindowFlags_AlwaysAutoResize);   
	Vector3 pos = _renderObjects[0].transform.position;
	gui::Text("Position:");
	gui::SameLine();
	if (gui::DragFloat3("##Position", &pos.x, 0.1f))
	{
		_renderObjects[0].transform.position = pos;
	}
	Quaternion rot = _renderObjects[0].transform.rotation;
	gui::Text("Rotation:");
	gui::SameLine();
	if (gui::DragFloat4("##Rotation", &rot.x, 0.01f))
	{
		_renderObjects[0].transform.rotation = rot;
	}
	Vector3 sca = _renderObjects[0].transform.scale;
	gui::Text("Scale:");
	gui::SameLine();
	if (gui::DragFloat3("##Scale", &sca.x, 0.1f))
	{
		_renderObjects[0].transform.scale = sca;
	}
	gui::Separator();
	gui::Text("RenderTarget");
	gui::Image(
		_renderTarget.GetRawData(),
		{ 128, 128 },
		{ 0, 0, },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	);

	gui::End();
	//gui::GetStyle().WindowPadding = ImVec2(0, 0);
	gui::Begin("Viewport", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	gui::Image(
		_renderTarget.GetRawData(),
		{ 512, 512 },
		{ 0, 0, },
		{ 1, 1 },
		{ 1, 1, 1, 1 },
		{ 1, 1, 1, 1 }
	);
	gui::End();

	SimpleDraw::AddGroundPlane(10, Colors::White);
	SimpleDraw::Draw(_camera);
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
