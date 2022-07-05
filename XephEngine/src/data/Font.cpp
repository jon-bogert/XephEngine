#include "Font.h"

xe::Font::Font(std::string path)
{
	//Note: path must be full path from project folder by this point
	font = new sf::Font;
	if (!font->loadFromFile(path))
		std::cout << "[INFO] Unable to open file at " << path << std::endl;
}

xe::Font::~Font()
{
	delete font;
}

std::string xe::Font::GetFamily() const
{
	return font->getInfo().family;
}

sf::Font* xe::Font::UnWrap()
{
	return font;
}
