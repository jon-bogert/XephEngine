#include "O_FPSCounter.h"

namespace O
{
	O::FPSCounter::FPSCounter()
		: GameObject() {transform = startTransform; LoadComponents();
	}

	void O::FPSCounter::LoadComponents()
	{
		AddComponent(new C::Text("default", 20, this));
		AddComponent(new C::FPSCounter(this));
	}
}
