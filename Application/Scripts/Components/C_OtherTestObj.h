#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class MyTestObj;
	class OtherTestObj : public Component
	{
	protected:
		MyTestObj* myTestObj = nullptr;
	
	public:
		OtherTestObj(GameObject* gameObject);
		
		void Start();
		void Update();
	};
}

