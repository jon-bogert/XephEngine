#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class MyTestObj : public Component
	{
	protected:
		//member variables here
	
	public:
		MyTestObj(GameObject* gameObject);
		
		void Start();
		void Update();

		void PrintTest();
	};
}

