#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace O
{
	class TestObj : public GameObject
	{
	public:
		Transform startTransform =
		{
			{9.f, 4.f}, // Position
			{0.f},		// Rotation
			{1.f, 1.f}  // Scale
		};

		TestObj();

	protected:
		void LoadComponents();
	};
}

