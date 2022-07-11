#include "World.h"

xe::World::~World()
{
	for (GameObject* go : gameObjects)
		delete go;
}

void xe::World::Start()
{
	for (GameObject* go : gameObjects)
		go->Start();
}

void xe::World::Update()
{
	for (GameObject* go : gameObjects)
	{
		if (go->GetIsActive())
			go->Update();
	}
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

void xe::World::DestroyGameObject(GameObject* gameObject)
{
	int index{};
	for (GameObject* go : gameObjects)
	{
		if (go == gameObject)
		{
			gameObjects.erase(gameObjects.begin() + index);
			delete gameObject;
			return;
		}
		else index++;
	}
	Debug::LogWarn("GameObject not destryed.");
}
