#pragma once
#include "../Libraries.h"
#include "Structs.h"
#include "Texture.h"

namespace xe
{
	class Texture;

	class Sprite
	{
		sf::Sprite* sprite;
		Rectangle frame;

	public:
		Sprite(xe::Texture* texture);
		~Sprite();

		sf::Sprite* UnWrap();

		void SetTexture(xe::Texture* texture, bool keepFrame = false);
		void SetFrame(int x, int y, int width, int height);
		void SetFrame(Rectangle _frame);
		
		Rectangle GetFrame() const;

		//TODO -> Origin, Color

	};
}

