#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace xe
{
	enum class ColliderType {Box, Circle};
}

namespace C
{
	class Collider : public Component
	{
	protected:
		ColliderType type;

		//Box
		float width = 0.f;
		float height = 0.f;

		//Circle
		float radius = 0.f;

		bool isTrigger{};
	
	public:
		Collider(ColliderType type, GameObject* gameObject);
		Collider(float width, float height, GameObject* gameObject); // for manual box
		Collider(float radius, GameObject* gameObject); // for manual circle
		~Collider();
		
		void Start();
		void Update();

		ColliderType GetType() const;

		Rectangle GetBox() const;
		Circle GetCircle() const;

		Collider* GetTrigger();
		//Collider* GetTriggerEnter();
		//Collider* GetTriggerExit();

	protected:
		bool BoxOnBox(Collider* other);
		bool CircleOnCircle(Collider* other);
		bool BoxOnCircle(Collider* other);
	};
}

