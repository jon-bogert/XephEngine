#include "O_OtherTestObj.h"

namespace O
{
	OtherTestObj::OtherTestObj()
		: GameObject() {transform=startTransform;LoadComponents();}
	
	void OtherTestObj::LoadComponents()
	{
		//AddComponent(new Component(this));

		AddComponent(new C::OtherTestObj(this));
	}
}
