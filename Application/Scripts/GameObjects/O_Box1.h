#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace O
{
	class Box1 : public GameObject
	{
	public:
		Transform startTransform =
		{
			{10.5f, 7.f}, // Position
			{0.f},		// Rotation
			{1.f, 1.f}  // Scale
		};
	
		Box1();
		
	protected:
		void LoadComponents();
	};
}

