#include "O_PhysicsCore.h"

namespace O
{
	PhysicsCore::PhysicsCore()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void PhysicsCore::LoadComponents()
	{
		//AddComponent(new Component(this));

		AddComponent(new C::PhysicsCore(this));
	}
}
