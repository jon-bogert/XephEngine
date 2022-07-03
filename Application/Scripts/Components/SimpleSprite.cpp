#include "SimpleSprite.h"

SimpleSprite::SimpleSprite(GameObject* gameObject)
	:Component(gameObject)
{
	AddDrawable();
	sprite = new sf::Sprite();
}

SimpleSprite::~SimpleSprite()
{
	delete sprite;
}
	
void SimpleSprite::Start()
{
	sprite->setTexture(*Engine::GetActiveScene()->FindTexture("test")->UnWrap());
}

void SimpleSprite::Update()
{
	
}

sf::Drawable* SimpleSprite::Draw()
{
	Draw::SpriteCalc(sprite, this);
	return sprite;
}
