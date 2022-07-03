#include "TestObj.h"

TestObj::TestObj()
	: GameObject()
{
	transform = startTransform;
	LoadComponents();
}

void TestObj::LoadComponents()
{
	//AddComponent(new TestComp(this));
	AddComponent(new SimpleSprite(this));
}
