#include "GameState.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;
using namespace xe;

namespace stdfs = std::filesystem;

void GameState::Initialize()
{
	_camera.SetPosition({ 0.f, 1.f, -15.f });
	_camera.SetLookAt({ 0.f, 0.f, 0.f });

	_directionalLight.direction = xe::Math::Normalize({ 1.f, -1.f, -1.f });

	stdfs::path path = L"../../Assets/Shaders/Standard.fx";
	_standardEffect.Initialize(path);

	_standardEffect.SetCamera(_camera);
	_standardEffect.SetDirectionalLight(_directionalLight);
	_standardEffect.SetLightCamera(_shadowEffect.GetLightCamera());
	_standardEffect.SetShadowMap(_shadowEffect.GetDephtMap());

	_bloomEffect.Initialize();
	_bloomEffect.SetBlurIterations(10);
	_bloomEffect.SetBlurSaturation(1.f);
	_bloomEffect.SetSourceTexture(_bloomRenderTarget);

	_shadowEffect.Initialize();
	_shadowEffect.SetDirectionalLight(_directionalLight);

	_postProcEffect.Initialize("../../Assets/Shaders/PostProc.fx");
	_postProcEffect.SetTexture(&_baseRenderTarget);
	_postProcEffect.SetTexture(&_bloomEffect.GetResultTexture(), 1);


	const uint32_t screenWidth = GraphicsSystem::Get().GetBackBufferWidth();
	const uint32_t screenHeight = GraphicsSystem::Get().GetBackBufferHeight();
	_baseRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	_bloomRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	_combineTexture.Initialize(L"../../Assets/Textures/water/water_texture.jpg");

	Mesh sphere = MeshBuilder::CreateUVSphere(128, 128, 1.f);

	_screenQuad.meshBuffer.Initialize(MeshBuilder::CreateScreenQuad());

	_sun.diffuseMapID = TextureManager::LoadTexture(L"planets/sun.jpg");
	_sun.meshBuffer.Initialize(MeshBuilder::CreateUVSphere(1024, 512, 5.f));
	_sun.material.emissive = Colors::White;
	_sun.material.power = 1.f;

	_earth.diffuseMapID = TextureManager::LoadTexture(L"planets/earth/earth.jpg");
	_earth.normalMapID = TextureManager::LoadTexture(L"planets/earth/earth_normal.jpg");
	_earth.displMapID = TextureManager::LoadTexture(L"planets/earth/earth_bump.jpg");
	_earth.specMapID = TextureManager::LoadTexture(L"planets/earth/earth_spec.jpg");
	_earth.meshBuffer.Initialize(MeshBuilder::CreateUVSphere(1024, 512, 1.f));
	_earth.material.ambient = { 0.5f, 0.5f, 0.5f, 1.f };
	_earth.material.diffuse = { 0.8f, 0.8f, 0.8f, 1.f };
	_earth.material.specular = {1.f, 1.f, 1.f, 1.f };
	_earth.material.power = 10.f;

	_earth.transform.position = { 0.f, 0.f, -8.f };
}

void GameState::Terminate()
{
	_screenQuad.Terminate();
	_combineTexture.Terminate();
	_postProcEffect.Terminate();
	_bloomEffect.Terminate();
	_bloomRenderTarget.Terminate();
	_baseRenderTarget.Terminate();
	_shadowEffect.Terminate();
	_standardEffect.Terminate();
}

void GameState::Update(const float& deltaTime)
{
	xe::Math::Quaternion::Rotate(_earth.transform.rotation, 0.5f * deltaTime, xe::Math::Vector3::YAxis);
	UpdateCameraControl(deltaTime);
	_shadowEffect.SetFocalPoint({ _camera.GetPosition().x, 0.f, _camera.GetPosition().z });
}

void GameState::Draw()
{
	_shadowEffect.Begin();
	_shadowEffect.End();

	_baseRenderTarget.BeginDraw(GraphicsSystem::Get().GetClearColor());
	_standardEffect.Begin();
	_standardEffect.Draw(_earth);
	_standardEffect.Draw(_sun);
	_standardEffect.End();
	SimpleDraw::AddGroundPlane(20.f, Colors::White);
	SimpleDraw::Draw(_camera);
	_baseRenderTarget.EndDraw();

	_bloomRenderTarget.BeginDraw();
	//Swap Material
	Material tempMat;
	tempMat.power = 1.f;
	std::swap(_earth.material, tempMat);
	_standardEffect.Begin();
	_standardEffect.Draw(_earth);
	_standardEffect.Draw(_sun);
	_standardEffect.End();
	//return material
	std::swap(_earth.material, tempMat);
	_bloomRenderTarget.EndDraw();

	_bloomEffect.Begin();
	_bloomEffect.Draw(_screenQuad);
	_bloomEffect.End();

	_postProcEffect.Begin();
	_postProcEffect.Draw(_screenQuad);
	_postProcEffect.End();
}

void GameState::DebugUI()
{
#ifdef _DEBUG
	ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_None);
	if (ImGui::CollapsingHeader("Lighting##", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::DragFloat3("Direction##Light", &_directionalLight.direction.x, 0.01f, -1.f, 1.f))
		{
			_directionalLight.direction = xe::Math::Normalize(_directionalLight.direction);
		}
		ImGui::NewLine();
		ImGui::ColorEdit4("Ambient##Light", &_directionalLight.ambient.r);
		ImGui::ColorEdit4("Diffuse##Light", &_directionalLight.diffuse.r);
		ImGui::ColorEdit4("Specular##Light", &_directionalLight.specular.r);

	}
	ImGui::NewLine();
	_standardEffect.DebugUI();
	_shadowEffect.DebugUI();
	_postProcEffect.DebugUI();
	_bloomEffect.DebugUI();
	ImGui::End();

#endif // _DEBUG
}

void GameState::UpdateCameraControl(const float& deltaTime)
{
	const float moveSpeed = InputSystem::GetKeyHold(Key::LShift) ? 10.f : 2.f;
	const float turnSpeed = 0.1f;

	Vector3 moveAxis = Vector3::Zero;

	if (InputSystem::GetKeyHold(Key::W))
	{
		moveAxis.z = 1;
	}
	if (InputSystem::GetKeyHold(Key::S))
	{
		moveAxis.z = -1;
	}
	if (InputSystem::GetKeyHold(Key::D))
	{
		moveAxis.x = 1;
	}
	if (InputSystem::GetKeyHold(Key::A))
	{
		moveAxis.x = -1;
	}
	if (InputSystem::GetKeyHold(Key::E))
	{
		moveAxis.y = 1;
	}
	if (InputSystem::GetKeyHold(Key::Q))
	{
		moveAxis.y = -1;
	}
	if (InputSystem::GetMouseHold(Mouse::Button::Right))
	{

		Vector2 mouseDelta;
		InputSystem::GetMouseDelta(&mouseDelta.x);
		_camera.Yaw(mouseDelta.x * turnSpeed * deltaTime);
		_camera.Pitch(mouseDelta.y * turnSpeed * deltaTime);
	}

	if (moveAxis == Vector3::Zero) return;

	moveAxis = Normalize(moveAxis) * moveSpeed * deltaTime;

	_camera.Walk(moveAxis.z);
	_camera.Strafe(moveAxis.x);
	_camera.Rise(moveAxis.y);
}
