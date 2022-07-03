#pragma once
#include "Libraries.h"
#include "Structs.h"
#include "Application.h"
#include "GameObject.h"
#include "Component.h"

namespace xe
{
	class GameObject;
	class Component;

	class Window
	{
		//Window Settings
		sf::RenderWindow* window;
		Vector2i resolution = {1920, 1080};
		Vector2i referenceResolution = {1920, 1080};
		float pixelsPerUnit = 100.f;
		float resolutionScale = 1.f;
		std::string title = "XephEngine Application";
		enum windowModeEnum {Windowed, Borderless, Fullscreen };
		windowModeEnum windowMode = Fullscreen;
		bool hasFrameLimit = false;
		int frameLimit = 60;

		//Frame Timing
		sf::Clock* clock;

		//Drawables
		std::vector<Component*> drawables{};

	public:
		Window();
		~Window();

		void Draw();

		bool IsOpen();
		void Close();
		sf::RenderWindow* SF_Window(); // TODO remove

		void UpdateResolutionScale();
		void UpdateFrameClock();
		void ResetFrameClock();

		std::vector<Component*>& GetDrawables();
		float GetPixelsPerUnit() const;
		float GetResolutionScale() const;
		float WidthInUnits() const;
		float HeightInUnits() const;

	protected:
		void DrawCalc(Component* comp);
	};

	namespace Time
	{
		float DeltaTime();
		float FPS();
		void UpdateDelta();
		void ResetDelta();
	}

	namespace Draw
	{
		void SpriteCalc(sf::Sprite* drawable, Component* comp);
	}
}

