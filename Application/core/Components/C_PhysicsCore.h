#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Collider;

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

	private:
		bool AABB(const Rectangle& rect1, const Rectangle& rect2);
	};
}

