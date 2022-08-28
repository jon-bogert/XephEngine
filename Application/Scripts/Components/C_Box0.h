#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Audio;
	class Box0 : public Component
	{
	protected:
		float speed = 1.f;

		Collider* collider = nullptr;
		Audio* audio = nullptr;
	
	public:
		Box0(GameObject* gameObject);
		
		void Start();
		void Update();
		void OnCollision(GameObject* other) override;
	};
}

