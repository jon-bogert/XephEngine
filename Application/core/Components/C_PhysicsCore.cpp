#include "C_PhysicsCore.h"

float COLLISION_OFFSET = 0.1f;

namespace C
{
	PhysicsCore::PhysicsCore(GameObject* gameObject)
		:Component(gameObject){}
		
	void PhysicsCore::Start()
	{
		if (FindObjectOfType<PhysicsCore>() != nullptr)
			Debug::LogErr("There can only be 1 PhysicsCore Component in the scene.");
	}
	
	void PhysicsCore::Update()
	{
		if (useGravity)
		{
			for (Collider* collider : colliders)
			{
				if (!collider->GetIsTrigger() && collider->GetHasGravity())
					collider->ApplyAcceleration(gravity);
			}
		}
	}

	void PhysicsCore::LateUpdate()
	{
		for (int i = 0; i < colliders.size(); i++)
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				//Check that one of the objects is not static
				if (!colliders[i]->GetIsStatic() || !colliders[j]->GetIsStatic())
				{
					if (AABB(colliders[i], colliders[j])) // TODO check new Position
					{
						//if one is trigger
						if ((colliders[i]->GetIsTrigger() || colliders[j]->GetIsTrigger()))
						{
							colliders[i]->GetGameObject()->OnTrigger(colliders[j]->GetGameObject());
							colliders[j]->GetGameObject()->OnTrigger(colliders[i]->GetGameObject());
						}
						else
						{

							//bool hasCollisionX = (AABB({destPosition.x, position.y, dimensions.x, dimensions.y }, *other));
							//bool hasCollisionY = (AABB({ position.x, destPosition.y, dimensions.x, dimensions.y }, *other));

							//if (hasCollisionX && (destPosition.x - position.x) > 0.f) // Positive X
							//	finalPosition.x = other->position.x - dimensions.x - COLLISION_OFFSET;
							//else if (hasCollisionX) // Negative X
							//	finalPosition.x = other->position.x + other->dimensions.x + COLLISION_OFFSET;

							//if (hasCollisionY && (destPosition.y - position.y) > 0.f) // Positive Y
							//{
							//	finalPosition.y = other->position.y - dimensions.y - COLLISION_OFFSET;
							//	velocity.y = 0;
							//}
							//else if (hasCollisionY) // Negative Y
							//	finalPosition.y = other->position.y + other->dimensions.y + COLLISION_OFFSET;



							colliders[i]->GetGameObject()->OnCollision(colliders[j]->GetGameObject()); // TODO Add Command Pattern and run after physics applied
							colliders[j]->GetGameObject()->OnCollision(colliders[i]->GetGameObject());
						}
					}
				}
			}
		}

		for (Collider* collider : colliders)
		{
			collider->PhysicsApply();
		}
	}

	Vector2 PhysicsCore::GetGravity() const
	{
		return gravity;
	}
	bool PhysicsCore::GetUseGravity() const
	{
		return useGravity;
	}
	void PhysicsCore::SetGravity(const Vector2 newGravity)
	{
		gravity = newGravity;
	}
	void PhysicsCore::SetUseGravity(const bool _useGravity)
	{
		useGravity = _useGravity;
	}
	void PhysicsCore::AddCollider(Collider* newCollider)
	{
		if (FindCollider(newCollider))
		{
			Debug::LogWarn("Added Collider already exists.");
			return;
		}

		colliders.push_back(newCollider);
	}
	void PhysicsCore::RemoveCollider(Collider* oldCollider)
	{
		int i = 0;
		while (i < colliders.size())
		{
			if (oldCollider == colliders[i])
			{
				colliders.erase(colliders.begin() + i);
				return;
			}
			else i++;
		}

		Debug::LogWarn("Collider to delete not found");
	}
	bool PhysicsCore::FindCollider(Collider* _collider)
	{
		for (Collider* collider : colliders)
		{
			if (collider == _collider)
				return true;
		}
		return false;
	}
	bool PhysicsCore::AABB(Collider* c1, Collider* c2)
	{
		return false;
	}
}
