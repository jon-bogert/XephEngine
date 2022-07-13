#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace O
{
	class Ground : public GameObject
	{
	public:
		Transform startTransform =
		{
			{10.f, 0.f}, // Position
			{0.f},		// Rotation
			{10.f, 1.f}  // Scale
		};
	
		Ground();
		
	protected:
		void LoadComponents();
	};
}

