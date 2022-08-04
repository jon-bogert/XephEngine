#pragma once
#include "../Libraries.h"

namespace xe
{
	class Utility
	{
		int menuSel = 0;

		sf::Color bgColor = { 20, 20, 20, 255 };
		sf::Color textColor = { 200, 200, 200, 255 };
		float fontSize = 20;

		sf::Font font;
		sf::RenderWindow* window = nullptr;

		sf::Text runText;
		sf::Text createText;

		sf::Texture logoTexture;
		sf::Sprite logoSprite;

	public:
		Utility();
		~Utility();

		int Runtime();

	private:
		void Update();
		void Draw();
	};
}

