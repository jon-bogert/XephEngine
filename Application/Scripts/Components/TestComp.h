#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class TestComp : public Component
{
protected:
	bool hasFired = false;

public:
	TestComp(GameObject* gameObject);

	void Start();
	void Update();
};

