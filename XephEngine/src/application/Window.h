#pragma once
#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"

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
		Color backgroundColor = Colour(0,0,0);

		//Frame Timing
		Timer* frameTimer;

		//Drawables
		std::vector<Component*> drawables{};

	public:
		Window();
		~Window();

		void Draw();

		bool IsOpen();
		void Close();
		sf::RenderWindow* UnWrap(); // TODO remove

		void UpdateResolutionScale();
		void UpdateFrameTimer();
		void ResetFrameTimer();

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
		void TextCalc(sf::Text* drawable, Component* comp);
	}
}

