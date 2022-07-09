#pragma once
#include "../../lib/XephEngine/Engine.h"

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
		bool isEnabled = true;
		bool drawable = false;
		void AddToDrawables(); //Call in on Start();
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
		virtual void OnEnable();
		virtual void OnDisable();
		virtual sf::Drawable* Draw();

		GameObject* GetGameObject();
		bool GetIsEnabled() const;
		void SetIsEnabled(const bool setTo);

		template <class T>
		T* GetComponent();

		
		template <class T>
		T* FindObjectOfType();

		GameObject* FindObjectByTag(std::string _tag);
	};


	template<class T>
	inline T* Component::GetComponent()
	{
		//class Name __cdecl(void)
		T temp();
		std::string raw = typeid(temp).name();
		std::string proc{};
		bool spaceCount{};
		for (char c : raw)
		{
			if (c == ' ' && spaceCount)
				break;
			if (c == ' ')
				spaceCount = true;

			proc.push_back(c);
		}
		for (xe::Component* comp : GetObjectComponents())
		{
			if (typeid(*comp).name() == proc) return (T*)comp;
		}
		return nullptr;
	}

	template<class T>
	inline T* Component::FindObjectOfType()
	{
		T temp();
		std::string raw = typeid(temp).name();
		std::string proc{};
		bool spaceCount{};
		for (char c : raw)
		{
			if (c == ' ' && spaceCount)
				break;
			if (c == ' ')
				spaceCount = true;

			proc.push_back(c);
		}
		std::vector<GameObject*> allObjects = GetAllGameObjects();
		for (GameObject* go : allObjects)
		{
			for (xe::Component* comp : go->GetComponents())
			{
				if (typeid(*comp).name() == proc) return (T*)comp;
			}
		}
		return nullptr;
	}
}

