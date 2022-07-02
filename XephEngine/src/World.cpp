#include "World.h"

xe::World::~World()
{
	for (GameObject* go : gameObjects)
		delete go;
}

void xe::World::LoadGameObjects()
{
}

std::vector<xe::GameObject*> xe::World::GetGameObjects()
{
	return gameObjects;
}

void xe::World::AddGameObject(GameObject* obj)
{
	gameObjects.push_back(obj);
}
