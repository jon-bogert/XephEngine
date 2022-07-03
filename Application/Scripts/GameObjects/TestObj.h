#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class TestObj : public GameObject
{
protected:
	Transform transform =
	{
		{0.f, 0.f}, // Position
		{0.f},		// Rotation
		{0.f, 0.f}  // Scale
	};

public:
	TestObj();

protected:
	void LoadComponents();
};

