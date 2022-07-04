#include "TestObj.h"

TestObj::TestObj()
	: GameObject()
{
	transform = startTransform;
	LoadComponents();
}

void TestObj::LoadComponents()
{
	AddComponent(new Text("default", 32, this));
	AddComponent(new TestComp(this));
}
