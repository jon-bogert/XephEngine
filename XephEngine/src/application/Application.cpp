#include "Application.h"
#include "../Libraries.h"
#include "../EngineUtils.h"

xe::Application* appRef;

namespace xe
{
	namespace Engine
	{
		Application* GetApplication()
		{
			return appRef;
		}

		Window* GetWindow()
		{
			return appRef->GetWindow();
		}

		Scene* GetActiveScene()
		{
			return appRef->GetActiveScene();
		}
	}

	Application::Application()
	{
		appRef = this;
		window = new Window();
		//scenes.push_back(new Scene()); // TODO Move to External Function
	}

	Application::~Application()
	{
		for (Scene* scene : scenes)
			delete scene;

		delete window;
		appRef = nullptr;
	}

	void Application::Runtime()
	{
		while (window->IsOpen())
		{
			scenes[buildIndex]->Runtime();
		}
	}

	void Application::AddScene(Scene* scene)
	{
		scenes.push_back(scene);
	}

	Window* Application::GetWindow()
	{
		return window;
	}
	Scene* Application::GetActiveScene()
	{
		return scenes[buildIndex];
	}
}
