#include "C_TestComp.h"

namespace C
{
	TestComp::TestComp(GameObject* gameObject)
		:Component(gameObject) {}

	void TestComp::Start()
	{
		text = GetComponent<C::Text>();
		//text->SetString("Boring...");
	}

	void TestComp::Update()
	{
		//std::string str = text->GetString();
		//InputSystem::Typing(str);
		//text->SetString(str);
		Vector2 v2 = InputSystem::KeyAxis2D(Key::D, Key::A, Key::S, Key::W);
		std::cout << "X:" << v2.x << " Y:" << v2.y << std::endl;

	}
}
