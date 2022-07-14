#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Collider;
	class TriggerCache : public Component
	{
	public:
		TriggerCache(GameObject* gameObject);
		std::vector<Collider*> triggers{};

		void Remove(Collider* collider);
	};
}

