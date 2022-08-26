#include "O_Ground.h"

namespace O
{
	Ground::Ground()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void Ground::LoadComponents()
	{
		AddComponent(new C::SimpleSprite("test", this));
		AddComponent(new C::Collider(10, 1, this));
		AddComponent(new C::Ground(this));
	}
}
