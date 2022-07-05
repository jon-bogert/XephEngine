#include "C_SimpleSprite.h"
namespace C
{
	SimpleSprite::SimpleSprite(std::string textureName, GameObject* gameObject)
		:Component(gameObject), textureName(textureName)
	{
		AddToDrawables();
	}

	SimpleSprite::~SimpleSprite()
	{
		delete sprite;
	}

	void SimpleSprite::Start()
	{
		SetTexture(textureName);
	}

	void SimpleSprite::Update()
	{

	}

	sf::Drawable* SimpleSprite::Draw()
	{
		Draw::SpriteCalc(sprite->UnWrap(), this);
		return sprite->UnWrap();
	}

	void SimpleSprite::SetTexture(std::string textureName)
	{
		if (sprite != nullptr) delete sprite;
		this->textureName = textureName;
		sprite = new Sprite(Engine::GetActiveScene()->FindTexture(textureName));
	}
}
