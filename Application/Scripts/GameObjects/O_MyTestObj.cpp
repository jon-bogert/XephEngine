#include "O_MyTestObj.h"

namespace O
{
	MyTestObj::MyTestObj()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void MyTestObj::LoadComponents()
	{
		//AddComponent(new Component(this));
		//AddComponent(new C::SimpleSprite("test", this));
		AddComponent(new C::SpriteSheet("test-ss", { 5, 3 }, { 100, 100 }, this));
		AddComponent(new C::MyTestObj(this));
	}
}
