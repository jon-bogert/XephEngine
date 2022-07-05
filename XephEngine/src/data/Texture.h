#pragma once
#include "../Libraries.h"
#include "Structs.h"

namespace xe
{
	class Texture
	{
		sf::Texture* texture;

	public:
		Texture(std::string path);
		~Texture();

		sf::Texture* UnWrap();
		Vector2i GetDimensions() const;
		void AntiAliased(const bool onOff);
		bool IsAntiAliased() const;
	};
}

