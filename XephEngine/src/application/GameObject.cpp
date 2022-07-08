#include "GameObject.h"


xe::GameObject::GameObject()
{
	Awake();
}

xe::GameObject::GameObject(GameObject* parent)
{
	SetParent(parent);
	parent->GetChildren().push_back(this);
	Awake();
}

xe::GameObject::GameObject(Transform tranform)
	: transform(transform)
{
	Awake();
}

xe::GameObject::GameObject(GameObject* parent, Transform transform)
	: transform(transform)
{
	SetParent(parent);
	parent->GetChildren().push_back(this);
	Awake();
}

xe::GameObject::~GameObject()
{
	for (Component* comp : components)
	{
		comp->OnDeath();
		delete comp;
	}
	if (parent != nullptr)
	{
		int i = 0;
		while (i < parent->GetChildren().size())
		{
			if (parent->GetChildren()[i] == this)
			{
				parent->GetChildren().erase(parent->GetChildren().begin() + i);
				break;
			}
		}
		for (GameObject* child : children)
		{
			child->SetParent(parent);
			parent->GetChildren().push_back(child);
		}
	}
	else
	{
		for (GameObject* child : children)
		{
			child->SetParent(nullptr);
		}
	}
}

void xe::GameObject::Awake()
{
	for (Component* comp : components) comp->Awake();
}

void xe::GameObject::Start()
{
	for (Component* comp : components)
	{
		comp->SetSceneRef();
		comp->Start();
	}
}

void xe::GameObject::Update()
{
	for (Component* comp : components) comp->Update();
}

void xe::GameObject::OnDeath()
{
	for (Component* comp : components) comp->OnDeath();
}

std::vector<xe::Component*> xe::GameObject::GetComponents()
{
	return components;
}

void xe::GameObject::SetParent(GameObject* newParent)
{
	parent = newParent;
}

std::vector<xe::GameObject*>& xe::GameObject::GetChildren()
{
	return children;
}

std::string xe::GameObject::GetTag() const
{
	return tag;
}

void xe::GameObject::SetTag(const std::string newTag)
{
	tag = newTag;
}

void xe::GameObject::LoadComponents()
{
}


xe::Component* xe::GameObject::AddComponent(Component* newComponent)
{
	components.push_back(newComponent);
	return newComponent;
}
