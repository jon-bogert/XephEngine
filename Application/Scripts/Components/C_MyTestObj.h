#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class SpriteSheet;
	class MyTestObj : public Component
	{
	protected:
		//member variables here
		SpriteSheet* ss = nullptr;
	
	public:
		MyTestObj(GameObject* gameObject);
		
		void Start();
		void Update();

		void PrintTest();
	};
}

