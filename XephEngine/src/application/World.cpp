#include "World.h"

xe::World::World()
{
	physicsWorld = new b2World({ gravity.x, gravity.y });
}

xe::World::~World()
{
	for (GameObject* go : gameObjects)
		go->OnDestroy();
	delete physicsWorld;
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
	physicsWorld->Step(Time::DeltaTime(), 6, 2); // TODO - Make Parameters
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

b2World* xe::World::PhysicsWorld()
{
	return physicsWorld;
}

xe::Vector2 xe::World::GetGravity() const
{
	return gravity;
}

void xe::World::SetGravity(Vector2 newGravity)
{
	gravity = newGravity;
	physicsWorld->SetGravity({ gravity.x, gravity.y });
}
