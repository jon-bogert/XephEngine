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
		float f = InputSystem::KeyAxis1D(Key::D, Key::A);
		std::cout << InputSystem::GetAxis(0, Axis::DPad) << f << std::endl;

	}
}
