#include "SimpleSprite.h"

SimpleSprite::SimpleSprite(GameObject* gameObject)
	:Component(gameObject)
{
	AddToDrawables();
}

SimpleSprite::~SimpleSprite()
{
	delete sprite;
	delete tempTexture;
}
	
void SimpleSprite::Start()
{
	//sprite = new Sprite(Engine::GetActiveScene()->FindTexture("test"));
	tempTexture = new Texture("Assets/Textures/test.png");
	sprite = new Sprite(tempTexture);

}

void SimpleSprite::Update()
{
	
}

sf::Drawable* SimpleSprite::Draw()
{
	Draw::SpriteCalc(sprite->UnWrap(), this);
	//std::cout << sprite->UnWrap()->getPosition().x << " " << sprite->UnWrap()->getPosition().y << std::endl;
	return sprite->UnWrap();
}
