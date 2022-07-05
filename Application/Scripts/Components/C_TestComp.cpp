#include "C_TestComp.h"

namespace C
{
	TestComp::TestComp(GameObject* gameObject)
		:Component(gameObject) {}

	void TestComp::Start()
	{
		GetComponent<C::Text>()->SetString("Hello There");
	}

	void TestComp::Update()
	{

	}
}
