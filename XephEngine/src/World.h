#pragma once
#include "Libraries.h"
#include "GameObject.h"
#include "Scene.h"


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

		std::vector<GameObject*> GetGameObjects();

	protected:
		virtual void LoadGameObjects();
		void AddGameObject(GameObject* obj);
	};
}

