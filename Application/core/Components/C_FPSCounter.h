#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Text;
	class FPSCounter : public Component
	{
	protected:
		Text* text = nullptr;

	public:
		C::FPSCounter(GameObject* gameObject);

		void Start();
		void Update();
	};
}

