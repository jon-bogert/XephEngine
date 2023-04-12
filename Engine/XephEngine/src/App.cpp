#include "Pch.h"
#include "App.h"
#include "AppState.h"

using namespace xe::Core;

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

	ASSERT(_currentState, "App -- No app state found");

	_currentState->Initialize();
	_isRunning = true;

	while (_isRunning)
	{
		window.ProcessMessage();
		if (!window.IsActive() || GetAsyncKeyState(VK_ESCAPE)) // TODO Remove ESC from here
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

		auto deltaTime = TimeUtil::DeltaTime();
		if (deltaTime < 0.5f)
		{
			_currentState->Update(deltaTime);
		}
	}

	_currentState->Terminate();

	window.Terminate();
}

void xe::App::Quit()
{
	_isRunning = false;
}
