#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class SimpleSprite : public Component
{
protected:
	sf::Sprite* sprite;

public:
	SimpleSprite(GameObject* gameObject);
	~SimpleSprite();
	
	void Start();
	void Update();
	sf::Drawable* Draw();
};

