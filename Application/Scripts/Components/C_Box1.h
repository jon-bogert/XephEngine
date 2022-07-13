#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Box1 : public Component
	{
	protected:
		//member variables here
	
	public:
		Box1(GameObject* gameObject);
		
		void Start();
		void Update();
	};
}

