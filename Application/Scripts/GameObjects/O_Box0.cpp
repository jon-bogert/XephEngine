#include "O_Box0.h"

namespace O
{
	Box0::Box0()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void Box0::LoadComponents()
	{
		AddComponent(new C::SimpleSprite("test", this));
		AddComponent(new C::Collider(1, 1, this));
		AddComponent(new C::Box0(this));
	}
}
