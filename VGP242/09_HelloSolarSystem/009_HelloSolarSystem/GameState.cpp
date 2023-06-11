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

	MeshPX skysphere = MeshBuilder::CreateSkyspherePX(32, 32, 128);

	//Skysphere
	_renderObjects.emplace_back();
	_renderObjects.back().meshBuffer.Initialize(skysphere);
	_renderObjects.back().diffuseTexture.Initialize(L"../../../Assets/Textures/skysphere/space.jpg");

	//Planets
	_planets.emplace_back().Init(Planet::Size::XL, L"Sun", 0.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::M, L"Mercury", 6.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::M, L"Venus", 8.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::M, L"Earth", 10.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::M, L"Mars", 12.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::L, L"Jupiter", 14.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::L, L"Saturn", 18.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::S, L"Uranus", 20.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::S, L"Neptune", 22.f, _renderObjects);
	_planets.emplace_back().Init(Planet::Size::S, L"Pluto", 24.f, _renderObjects);

	_simpleEffect.Initialize();
	_simpleEffect.SetCamera(_camera);

	constexpr uint32_t size = 512;
	_renderTarget.Initialize(size, size, Texture::Format::RGBA_U32);
}

void GameState::Terminate()
{
	_renderTarget.Terminate();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
	{
		it->Terminate();
	}
	_simpleEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	UpdateCameraControl(deltaTime);
	for (Planet& p : _planets)
	{
		p.Update(deltaTime);
	}
}

void GameState::Draw()
{
	_simpleEffect.Begin();
	for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
	{
		_simpleEffect.Draw(*it);
	}
	_simpleEffect.End();

	float origRatio = _camera.GetAspectRatio();
	_camera.SetAspectRatio(1.f);
	_renderTarget.BeginDraw();
	{
		_simpleEffect.Begin();
		for (auto it = _renderObjects.begin(); it != _renderObjects.end(); ++it)
		{
			_simpleEffect.Draw(*it);
		}
		_simpleEffect.End();
	}
	_renderTarget.EndDraw();
	_camera.SetAspectRatio(origRatio);
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	gui::Begin("Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	gui::Text("Show Orbit:");
	gui::SameLine();
	bool showOrbit = _planets[0].GetShowOrbit();
	if (gui::Checkbox("##ShowOrbit", &showOrbit))
		for (Planet& p : _planets)
			p.SetShowOrbit(showOrbit);

	for (Planet& p : _planets)
	{
		if (p.GetPlanetName() == "Sun") continue;
		gui::Text((p.GetPlanetName()).c_str());
		gui::Text("    Orbit:");
		gui::SameLine();
		float orbit = p.GetOrbitSpeed();
		if (gui::DragFloat(("##Orbit" + p.GetPlanetName()).c_str(), &orbit, 0.01f))
			p.SetOrbitSpeed(orbit);
		gui::Text("      Day:");
		gui::SameLine();
		float day = p.GetDayRotSpeed();
		if (gui::DragFloat(("##Day" + p.GetPlanetName()).c_str(), &day, 0.01f))
			p.SetDayRotSpeed(day);
		gui::NewLine();
	}

	gui::End();

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
