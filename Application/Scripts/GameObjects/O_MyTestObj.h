#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace O
{
	class MyTestObj : public GameObject
	{
	public:
		Transform startTransform =
		{
			{0.f, 0.f}, // Position
			{0.f},		// Rotation
			{1.f, 1.f}  // Scale
		};
	
		MyTestObj();
		
	protected:
		void LoadComponents();
	};
}

