#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class TestComp : public Component
	{
	protected:

	public:
		TestComp(GameObject* gameObject);

		void Start();
		void Update();
	};
}

