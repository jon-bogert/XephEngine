#include "C_TestComp.h"

namespace C
{
	TestComp::TestComp(GameObject* gameObject)
		:Component(gameObject) {}

	void TestComp::Start()
	{
		text = GetComponent<C::Text>();
		text->SetString("Boring...");
	}

	void TestComp::Update()
	{
		if (InputSystem::KeyDown(Key::Space))
			text->SetString("YAYYYYY!!!!");
		else
			text->SetString("Boring...");
	}
}
