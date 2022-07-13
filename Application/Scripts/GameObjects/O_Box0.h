#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace O
{
	class Box0 : public GameObject
	{
	public:
		Transform startTransform =
		{
			{10.f, 9.f}, // Position
			{0.f},		// Rotation
			{1.f, 1.f}  // Scale
		};
	
		Box0();
		
	protected:
		void LoadComponents();
	};
}

