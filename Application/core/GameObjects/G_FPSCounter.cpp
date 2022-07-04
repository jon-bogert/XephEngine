#include "G_FPSCounter.h"

G_FPSCounter::G_FPSCounter()
	: GameObject() {transform = startTransform; LoadComponents();}

void G_FPSCounter::LoadComponents()
{
	AddComponent(new Text("default", 20, this));
	AddComponent(new C_FPSCounter(this));
}
