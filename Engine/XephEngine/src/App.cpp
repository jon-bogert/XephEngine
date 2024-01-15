#include "Pch.h"
#include "App.h"
#include "AppState.h"

using namespace xe::Core;
using namespace xe::Graphics;
using namespace xe::Physics;
using namespace xe;

void xe::App::ChangeState(const std::string& stateName)
{
	auto iter = m_appStates.find(stateName);
	if (iter != m_appStates.end())
	{
		m_nextState = iter->second.get();
	}
}

void xe::App::Run(const AppConfig& config)
{
	Window window;
	window.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);

	HWND handle = window.GetWindowHandle();
	GraphicsSystem::Initialize(handle, false);
	InputSystem::Initialize(handle);
	DebugUI::Initialize(handle, false, true);
	SimpleDraw::Initialize(config.debugDrawLimit);
	TextureManager::Initialize("../../Assets/Textures");
	ModelManager::Initialize();

	PhysicsWorld::Settings physSettings;
	PhysicsWorld::Initialize(physSettings);

	ASSERT(m_currentState, "App -- No app state found");

	m_currentState->Initialize();
	m_isRunning = true;

	

	while (m_isRunning)
	{
		window.ProcessMessage();

		InputSystem::Update();
		if (!window.IsActive() || InputSystem::GetKeyDown(xe::Key::Esc)) // TODO Remove ESC from here
		{
			Quit();
			continue;
		}

		if (m_nextState != nullptr)
		{
			m_currentState->Terminate();
			m_currentState = std::exchange(m_nextState, nullptr);
			m_currentState->Initialize();
		}

		auto deltaTime = TimeUtil::DeltaTime();
		if (deltaTime < 0.5f)
		{
			PhysicsWorld::Update(deltaTime);
			m_currentState->Update(deltaTime);
		}

		GraphicsSystem& graphicsSystem = GraphicsSystem::Get();
		graphicsSystem.BeginRender();
		{
			m_currentState->Draw();
			DebugUI::BeginDraw();
			{
				m_currentState->DebugUI();
			}
			DebugUI::EndDraw();
		}
		graphicsSystem.EndRender();
	}

	m_currentState->Terminate();
	PhysicsWorld::Terminate();
	ModelManager::Terminate();
	TextureManager::Terminate();
	SimpleDraw::Terminate();
	DebugUI::Terminate();
	GraphicsSystem::Terminate();
	window.Terminate();
}

void xe::App::Quit()
{
	m_isRunning = false;
}
