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

void xe::Component::AddToDrawables()
{
	drawable = true;
	Engine::GetWindow()->GetDrawables().push_back(this);
}

void xe::Component::RemoveDrawable()
{
	if (drawable)
	{
		for (int i = 0; i < Engine::GetWindow()->GetDrawables().size(); i++)
		{
			if (Engine::GetWindow()->GetDrawables()[i] == this)
				Engine::GetWindow()->GetDrawables().erase(Engine::GetWindow()->GetDrawables().begin() + i); return;
		}
		Debug::Log("Component type: %s was tagged as 'Drawable' incorrectly", typeid(*this).name());
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

void xe::Component::OnDestroy()
{
}

void xe::Component::OnEnable()
{
}

void xe::Component::OnDisable()
{
}

sf::Drawable* xe::Component::Draw()
{
	return nullptr;
}

xe::GameObject* xe::Component::GetGameObject()
{
	return gameObject;
}

bool xe::Component::GetIsEnabled() const
{
	return isEnabled;
}

void xe::Component::SetIsEnabled(const bool setTo)
{
	if (isEnabled != setTo)
	{
		if (setTo)
			OnEnable();
		else
			OnDisable();
	}
	isEnabled = setTo;
}

void xe::Component::Instantiate(GameObject* gameObject)
{
	Engine::GetActiveScene()->GetWorld()->AddGameObject(gameObject);
	gameObject->Start();
}

void xe::Component::Destroy(GameObject* gameObject)
{
	if (gameObject != nullptr)
	{
		gameObject->OnDestroy();
		Engine::GetActiveScene()->GetWorld()->DestroyGameObject(gameObject);
	}
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
