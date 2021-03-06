#include "Sprite.h"
#include "../EngineUtils.h"

xe::Sprite::Sprite(xe::Texture* texture)
{
	sprite = new sf::Sprite();
	SetTexture(texture);
}

xe::Sprite::~Sprite()
{
	delete sprite;
}

sf::Sprite* xe::Sprite::UnWrap()
{
	return sprite;
}

void xe::Sprite::SetTexture(xe::Texture* texture, bool keepFrame)
{
	sprite->setTexture(*texture->UnWrap());

	if (keepFrame)
		SetFrame(frame);
	else
		SetFrame(Rectangle(0, 0, texture->GetDimensions().x, texture->GetDimensions().y));
	
}

void xe::Sprite::SetFrame(int x, int y, int width, int height)
{
	SetFrame(Rectangle(x, y, width, height));
	sprite->setOrigin(width * 0.5f, height * 0.5f);
}

void xe::Sprite::SetFrame(Rectangle _frame)
{
	frame = _frame;
	sprite->setTextureRect((sf::IntRect)Engine::SF_RECT(frame));
	sprite->setOrigin(frame.width * 0.5f, frame.height * 0.5f);
}

xe::Rectangle xe::Sprite::GetFrame() const
{
	return frame;
}

