#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Ground : public Component
	{
	protected:
		//member variables here
	
	public:
		Ground(GameObject* gameObject);
		
		void Start();
		void Update();
	};
}

