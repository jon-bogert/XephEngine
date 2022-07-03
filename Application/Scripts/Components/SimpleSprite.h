#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class SimpleSprite : public Component
{
protected:
	Sprite* sprite = nullptr;
	Texture* tempTexture = nullptr; // TODO Use from Scene

public:
	SimpleSprite(GameObject* gameObject);
	~SimpleSprite();
	
	void Start();
	void Update();
	sf::Sprite* DrawSprite();
};

