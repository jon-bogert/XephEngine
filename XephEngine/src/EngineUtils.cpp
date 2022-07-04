#include "EngineUtils.h"

namespace xe
{
	namespace Engine
	{
		sf::Vector2<float> SF_Vector2(Vector2 v2)
		{
			return sf::Vector2<float> { v2.x, v2.y };
		}
		//Vector2 SF_Vector2(sf::Vector2<float> v2)
		//{
		//	return Vector2{ v2.x, v2.y };
		//}
		Vector2 SF_Vector2(sf::Vector2f v2)
		{
			return Vector2{ v2.x, v2.y };
		}
		Vector2 SF_Vector2(sf::Vector2u v2)
		{
			return Vector2{ (float)v2.x, (float)v2.y };
		}
		Vector2i SF_Vector2i(sf::Vector2u v2)
		{
			return Vector2i{ (int)v2.x, (int)v2.y };
		}
		sf::Rect<float> SF_RECT(Rectangle r)
		{
			return sf::Rect<float>(r.x, r.y, r.width, r.height);
		}
		Rectangle SF_RECT(sf::FloatRect r)
		{
			return Rectangle(r.left, r.top, r.width, r.height);
		}
		sf::Color SF_COLOR(Color c)
		{
			return sf::Color(c.r, c.g, c.b, c.a);
		}
		Color SF_COLOR(sf::Color c)
		{
			return Color(c.r, c.g, c.b, c.a);
		}
	}
}