#pragma once
#include "XephEngine/Engine.h"
#include "../src/Resources.h"

using namespace xe;

class TestObj : public GameObject
{
public:
	Transform startTransform =
	{
		{5.f, 0.f}, // Position
		{0.f},		// Rotation
		{1.f, 1.f}  // Scale
	};

	TestObj();

protected:
	void LoadComponents();
};

