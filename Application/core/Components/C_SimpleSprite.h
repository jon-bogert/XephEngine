#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class SimpleSprite : public Component
	{
	protected:
		Sprite* sprite = nullptr;
		std::string textureName{};

	public:
		SimpleSprite(std::string textureName, GameObject* gameObject);
		~SimpleSprite();

		void Start();
		void Update();
		sf::Drawable* Draw();

		void SetTexture(std::string textureName);
		Rectangle GetFrame() const;
	};
}

