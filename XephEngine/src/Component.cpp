#include "Component.h"

std::vector<xe::GameObject*> xe::Component::GetAllGameObjects()
{
	return sceneRef->GetWorld()->GetGameObjects();
}

std::vector<xe::Component*> xe::Component::GetObjectComponents()
{
	return gameObject->GetComponents();
}

void xe::Component::SetSceneRef()
{
	sceneRef = Engine::GetActiveScene();
}

void xe::Component::AddSprite()
{
	drawable = true;
	Engine::GetWindow()->GetSprites().push_back(this);
}

void xe::Component::RemoveDrawable()
{
	if (drawable)
	{
		for (int i = 0; i < Engine::GetWindow()->GetSprites().size(); i++)
		{
			if (Engine::GetWindow()->GetSprites()[i] == this)
				Engine::GetWindow()->GetSprites().erase(Engine::GetWindow()->GetSprites().begin() + i); return;
		}
		std::cout << "[INFO] Component type: " << typeid(*this).name() << " was tagged as 'Drawable' incorrectly" << std::endl;
	}
}

xe::Component::Component(GameObject* gameObject)
	: gameObject(gameObject)
{
}

xe::Component::~Component()
{
	RemoveDrawable();
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

sf::Sprite* xe::Component::DrawSprite()
{
	return nullptr;
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

	return nullptr;
}
