#pragma once
#include "../Libraries.h"
#include "../../lib/XephEngine/Engine.h"


namespace xe
{
	class GameObject;
	class Scene;

	class World
	{
	protected:
		std::vector<GameObject*> gameObjects;
		b2World* physicsWorld = nullptr;
		Vector2 gravity{ 0.f, -9.8f };

	public:
		World();
		~World();

		void Start();
		void Update();

		std::vector<GameObject*> GetGameObjects();
		void AddGameObject(GameObject* obj);
		void DestroyGameObject(GameObject* gameObject);

		b2World* PhysicsWorld();
		Vector2 GetGravity() const;
		void SetGravity(Vector2 newGravity);

	protected:
		virtual void LoadGameObjects();
	};

	enum class PhysicsBody {Static, Dynamic, Kinematic};
}

