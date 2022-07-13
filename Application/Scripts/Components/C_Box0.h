#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Box0 : public Component
	{
	protected:
		//member variables here
	
	public:
		Box0(GameObject* gameObject);
		
		void Start();
		void Update();
	};
}

