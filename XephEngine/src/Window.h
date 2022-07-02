#pragma once
#include "Libraries.h"
#include "Structs.h"

namespace xe
{
	class Window
	{
		sf::RenderWindow* window;
		Vector2i resolution = {1920, 1080};
		Vector2i referenceResolution = {1920, 1080};
		float pixelsPerUnit = 10.f;
		std::string title = "XephEngine Application";
		enum windowModeEnum {Windowed, Borderless, Fullscreen };
		windowModeEnum windowMode = Fullscreen;
		bool hasFrameLimit = false;
		int frameLimit = 60;

	public:
		Window();
		~Window();

		void Draw();

		bool IsOpen();
		void Close();

	};
}

