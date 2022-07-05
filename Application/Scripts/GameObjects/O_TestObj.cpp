#include "O_TestObj.h"

namespace O
{
	TestObj::TestObj()
		: GameObject()
	{
		transform = startTransform;
		LoadComponents();
	}

	void TestObj::LoadComponents()
	{
		AddComponent(new C::Text("default", 32, this));
		AddComponent(new C::TestComp(this));
	}
}
