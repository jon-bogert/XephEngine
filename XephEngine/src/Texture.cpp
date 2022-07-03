#include "Texture.h"
#include "EngineUtils.h"

xe::Texture::Texture(std::string path/*, std::string name*/)
	//: name(name)
{
	//Note: path must be full path from project folder by this point
	texture = new sf::Texture();
	if (!texture->loadFromFile(path))
		std::cout << "[INFO] Unable to open file at " << path << std::endl;
}

xe::Texture::~Texture()
{
	delete texture;
}

sf::Texture* xe::Texture::UnWrap()
{
	return texture;
}

xe::Vector2i xe::Texture::GetDimensions() const
{
	return Engine::SF_Vector2i(texture->getSize());
}

void xe::Texture::AntiAliased(const bool onOff)
{
	texture->setSmooth(onOff);
}

bool xe::Texture::IsAntiAliased() const
{
	return texture->isSmooth();
}

//std::string xe::Texture::GetName() const
//{
//	return name;
//}
