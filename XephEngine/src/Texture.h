#pragma once
#include "Libraries.h"
#include "Structs.h"

namespace xe
{
	class Texture
	{
		sf::Texture* texture;
		//std::string name;

	public:
		Texture(std::string path/*, std::string name*/);
		~Texture();

		sf::Texture* UnWrap();
		Vector2i GetDimensions() const;
		void AntiAliased(const bool onOff);
		bool IsAntiAliased() const;

		//std::string GetName() const;
	};
}

