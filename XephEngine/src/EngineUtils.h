#pragma once
#include "Libraries.h"
#include "Structs.h"

namespace xe
{
	namespace Engine
	{
		sf::Vector2<float> SF_Vector2(Vector2 v2);
		Vector2 SF_Vector2(sf::Vector2<float> v2);
		Vector2 SF_Vector2(sf::Vector2f v2);
		Vector2 SF_Vector2(sf::Vector2u v2);
		Vector2i SF_Vector2i(sf::Vector2u v2);
	}
}