#include "O_Box1.h"

namespace O
{
	Box1::Box1()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void Box1::LoadComponents()
	{
		AddComponent(new C::SimpleSprite("test-circle", this));
		//AddComponent(new C::PhysicsBox(PhysicsBody::Dynamic, { 1, 1 }, this));
		AddComponent(new C::Collider(0.5f, this));
		AddComponent(new C::Box1(this));
	}
}
