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

	public:
		World();
		~World();

		void Start();
		void Update();

		std::vector<GameObject*> GetGameObjects();
		void AddGameObject(GameObject* obj);
		void DestroyGameObject(GameObject* gameObject);

	protected:
		virtual void LoadGameObjects();
	};

	enum class PhysicsBody {Static, Dynamic, Kinematic};
}

