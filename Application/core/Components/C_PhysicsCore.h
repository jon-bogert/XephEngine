#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class PhysicsCore : public Component
	{
	protected:
		std::vector<Collider*> colliders;
		Vector2 gravity = { 0.f, -9.8 };
		bool useGravity = false;
	
	public:
		PhysicsCore(GameObject* gameObject);
		
		void Start();
		void Update();
		void LateUpdate();

		Vector2 GetGravity() const;
		bool GetUseGravity() const;
		void SetGravity(const Vector2 gravity);
		void SetUseGravity(const bool _useGravity);
		
		void AddCollider(Collider* newCollider);
		void RemoveCollider(Collider* oldCollider);
		bool FindCollider(Collider* _collider);
		bool AABB(Collider* c1, Collider* c2);
		bool AABB(const float aLeft, const float aTop, const float aRight, const float aBottom, const float bLeft, const float bTop, const float bRight, const float bBottom);
	};
}

