#pragma once
#include "Libraries.h"

namespace xe
{
	class Font
	{
		sf::Font* font;

	public:
		Font(std::string path);
		~Font();

		std::string GetFamily() const;
		sf::Font* UnWrap();
	};
}

