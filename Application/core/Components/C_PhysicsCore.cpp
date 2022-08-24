#include "C_PhysicsCore.h"

float COLLISION_OFFSET = 0.001f;

namespace C
{
	PhysicsCore::PhysicsCore(GameObject* gameObject)
		:Component(gameObject){}
		
	void PhysicsCore::Start()
	{
		//if (FindObjectOfType<PhysicsCore>() != nullptr) // TODO - Check if List is greater than 1
		//	Debug::LogErr("There can only be 1 PhysicsCore Component in the scene."); 
	}
	
	void PhysicsCore::Update()
	{
		if (useGravity)
		{
			for (Collider* collider : colliders)
			{
				if (collider->GetHasGravity())
					collider->ApplyAcceleration(gravity);
			}
		}
	}

	void PhysicsCore::LateUpdate()
	{
		for (Collider* collider : colliders)
		{
			collider->ApplyCurrentVelocity();
		}

		for (int i = 0; i < colliders.size(); i++)
		{
			for (int j = i + 1; j < colliders.size(); j++)
			{
				//Check that one of the objects is not static
				if (!colliders[i]->GetIsStatic() || !colliders[j]->GetIsStatic())
				{
					if (AABB(colliders[i]->MoveBufferRect(), colliders[j]->MoveBufferRect()))
					{
						//if one is trigger
						if ((colliders[i]->GetIsTrigger() || colliders[j]->GetIsTrigger()))
						{
							colliders[i]->GetGameObject()->OnTrigger(colliders[j]->GetGameObject());
							colliders[j]->GetGameObject()->OnTrigger(colliders[i]->GetGameObject());
						}
						else
						{

							bool hasCollisionX = (AABB(colliders[i]->MoveBufferRectX(), colliders[j]->MoveBufferRectX()));
							bool hasCollisionY = (AABB(colliders[i]->MoveBufferRectY(), colliders[j]->MoveBufferRectY()));

							Collider* slower = nullptr;
							Collider* faster = nullptr;

							if (hasCollisionX)
							{
								if (fabsf(colliders[i]->GetMoveBuffer().x) > fabsf(colliders[j]->GetMoveBuffer().x))
								{
									slower = colliders[j];
									faster = colliders[i];
								}
								else
								{
									slower = colliders[i];
									faster = colliders[j];
								}

								if (faster->GetMoveBuffer().x > 0.f) // Positive X
									faster->SetMoveBuffer({ slower->GetLeft() - faster->GetDimensions().x - COLLISION_OFFSET - faster->GetLeft(), faster->GetMoveBuffer().y});
								else if (hasCollisionX) // Negative X
									faster->SetMoveBuffer({ slower->GetLeft() + slower->GetDimensions().x + COLLISION_OFFSET - faster->GetLeft(), faster->GetMoveBuffer().y });

								faster->SetVelocity({ 0.f, faster->GetVelocity().y });
								if (!slower->GetIsStatic()) slower->SetVelocity({ 0.f, slower->GetVelocity().y });
							}
							else // collision Y
							{
								if (fabsf(colliders[i]->GetMoveBuffer().y) > fabsf(colliders[j]->GetMoveBuffer().y))
								{
									slower = colliders[j];
									faster = colliders[i];
								}
								else
								{
									slower = colliders[i];
									faster = colliders[j];
								}

								if (faster->GetMoveBuffer().y > 0.f) // Positive Y
									faster->SetMoveBuffer({ faster->GetMoveBuffer().x,  slower->GetBottom() - faster->GetDimensions().y - COLLISION_OFFSET - faster->GetBottom()});
								else if (hasCollisionY) // Negative Y
									faster->SetMoveBuffer({ faster->GetMoveBuffer().x,  slower->GetBottom() + slower->GetDimensions().y + COLLISION_OFFSET - faster->GetBottom()});

								faster->SetVelocity({ faster->GetVelocity().x, 0.f });
								if (!slower->GetIsStatic()) slower->SetVelocity({ slower->GetVelocity().x, 0.f });
							}

							colliders[i]->GetGameObject()->OnCollision(colliders[j]->GetGameObject()); // TODO Add Command Pattern and run after physics applied
							colliders[j]->GetGameObject()->OnCollision(colliders[i]->GetGameObject());
						}
					}
				}
			}
		}

		for (Collider* collider : colliders)
		{
			if (!collider->GetIsStatic()) collider->PhysicsApply();
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
	bool PhysicsCore::AABB(const Rectangle& rect1, const Rectangle& rect2)
	{
		return (rect1.x < rect2.x + rect2.width &&
			rect1.x + rect1.width > rect2.x &&
			rect1.y < rect2.y + rect2.height &&
			rect1.y + rect1.height > rect2.y);
	}
}
