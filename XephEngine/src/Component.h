#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "Application.h"

namespace xe
{
	class GameObject;
	class Scene;

	class Component
	{
	private:
		Scene* sceneRef = nullptr;
		std::vector<GameObject*> GetAllGameObjects();
		std::vector<Component*> GetObjectComponents();

	protected:
		GameObject* gameObject = nullptr;
		bool drawable = false;
		void AddDrawable(); //Call in on Start();
		void RemoveDrawable(); // Called on Destructor

	public:
		Component(GameObject* gameObject);
		Component() = default;
		~Component();

		void SetSceneRef();

		virtual void Awake();
		virtual void Start();
		virtual void Update();
		virtual void OnDeath();
		virtual sf::Drawable* Draw();

		GameObject* GetGameObject();

		template <class T>
		T* GetComponent();
		
		template <class T>
		T* FindObjectOfType();

		GameObject* FindObjectByTag(std::string _tag);
	};


	template<class T>
	inline T* Component::GetComponent()
	{
		T temp();

		for (xe::Component* comp : GetObjectComponents())
		{
			if (typeid(*comp).name() == typeid(temp).name()) return comp;
		}
		return nullptr;
	}

	template<class T>
	inline T* Component::FindObjectOfType()
	{
		std::vector<GameObject*> allObjects = GetAllGameObjects();
		for (GameObject* go : allObjects)
		{
			if (go->GetComponent<T>() != nullptr)
				return go->GetComponent<T>();
		}
		return nullptr;
	}
}

