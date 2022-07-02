#include "Component.h"

std::vector<xe::GameObject*> xe::Component::GetAllGameObjects()
{
	return sceneRef->GetWorld()->GetGameObjects();
}

std::vector<xe::Component*> xe::Component::GetObjectComponents()
{
	return gameObject->GetComponents();
}

xe::Component::Component(GameObject* gameObject)
	: gameObject(gameObject), sceneRef(Engine::GetActiveScene())
{
}

void xe::Component::Awake()
{
}

void xe::Component::Start()
{
}

void xe::Component::Update()
{
}

void xe::Component::OnDeath()
{
}

xe::GameObject* xe::Component::GetGameObject()
{
	return gameObject;
}

xe::GameObject* xe::Component::FindObjectByTag(std::string _tag)
{
	//for (GameObject* go : Engine::GetActiveScene()->GetWorld()->GetGameObjects())
	//{
	//	if (go->GetTag() == _tag)
	//		return go;
	//}
	Engine::EngineTest();

	return nullptr;
}
