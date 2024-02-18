#include "Pch.h"
#include "App.h"
#include "AppState.h"

using namespace xe::Core;
using namespace xe::Graphics;
using namespace xe::Physics;
using namespace xe::Audio;
using namespace xe;

void xe::App::ChangeState(const std::string& stateName)
{
	auto iter = _appStates.find(stateName);
	if (iter != _appStates.end())
	{
		_nextState = iter->second.get();
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
	AudioSystem::Initialize();
	SoundEffectManager::Initialize("../../Assets/Audio");

	PhysicsWorld::Settings physSettings;
	PhysicsWorld::Initialize(physSettings);

	ASSERT(_currentState, "App -- No app state found");

	_currentState->Initialize();
	_isRunning = true;

	

	while (_isRunning)
	{
		window.ProcessMessage();

		InputSystem::Update();
		if (!window.IsActive() || InputSystem::GetKeyDown(xe::Key::Esc)) // TODO Remove ESC from here
		{
			Quit();
			continue;
		}

		if (_nextState != nullptr)
		{
			_currentState->Terminate();
			_currentState = std::exchange(_nextState, nullptr);
			_currentState->Initialize();
		}

		AudioSystem::Update();

		auto deltaTime = TimeUtil::DeltaTime();
		if (deltaTime < 0.5f)
		{
			//PhysicsWorld::Update(deltaTime); -> Moved to Service
			_currentState->Update(deltaTime);
		}

		GraphicsSystem& graphicsSystem = GraphicsSystem::Get();
		graphicsSystem.BeginRender();
		{
			_currentState->Draw();
			DebugUI::BeginDraw();
			{
				_currentState->DebugUI();
			}
			DebugUI::EndDraw();
		}
		graphicsSystem.EndRender();
	}

	_currentState->Terminate();
	PhysicsWorld::Terminate();
	ModelManager::Terminate();
	SoundEffectManager::Terminate();
	AudioSystem::Terminate();
	TextureManager::Terminate();
	SimpleDraw::Terminate();
	DebugUI::Terminate();
	GraphicsSystem::Terminate();
	window.Terminate();
}

void xe::App::Quit()
{
	_isRunning = false;
}
