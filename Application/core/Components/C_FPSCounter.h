#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;
class Text;

class C_FPSCounter : public Component
{
protected:
	Text* text = nullptr;

public:
	C_FPSCounter(GameObject* gameObject);
	
	void Start();
	void Update();
};

