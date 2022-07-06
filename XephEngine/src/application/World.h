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
		World() = default; // TODO load GameObjects from external function
		~World();

		void Start();
		void Update();

		std::vector<GameObject*> GetGameObjects();

	protected:
		virtual void LoadGameObjects();
		void AddGameObject(GameObject* obj);
	};
}
