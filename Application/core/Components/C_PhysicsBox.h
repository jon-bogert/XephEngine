#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class PhysicsBox : public Component
	{
	protected:
		b2BodyDef* bodyDef = nullptr;
		b2Body* body = nullptr;
		b2PolygonShape* shape = nullptr;
		b2FixtureDef* fixtureDef = nullptr;
		Vector2 dimensions;

		float density = 1.f;
		float friction = 0.3f;
	
	public:
		PhysicsBox(PhysicsBody bodyType, Vector2 dimensions, GameObject* gameObject);
		~PhysicsBox();
		
		void Start();
		void Update();
		
		void AddImpulse(Vector2 impulse);
	};
}

