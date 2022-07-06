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
		InputSystem::TestFunction();

	}
}
