#pragma once
#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"

namespace xe
{
	class Scene;
	class Window;

	class Application
	{
		Window* window;
		std::vector<Scene*> scenes;
		int buildIndex = 0;

	public:
		Application();
		~Application();

		void AddScene(Scene* scene);
		void Runtime();

		Window* GetWindow();
		Scene* GetActiveScene();
	};

	namespace Engine
	{
		Application* GetApplication();
		Window* GetWindow();
		Scene* GetActiveScene();
	}
}

