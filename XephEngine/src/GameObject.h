#pragma once
#include "Libraries.h"
#include "Structs.h"
#include "Component.h"

namespace xe
{
	class Component;
	class GameObject;

	class GameObject
	{
	protected:
		Transform transform{};
		std::string tag{};
		std::vector<Component*> components{};
		GameObject* parent = nullptr;
		std::vector<GameObject*> children{};

		void Awake();
		void OnDeath();

	public:
		GameObject();
		GameObject(GameObject* parent);
		GameObject(Transform tranform);
		GameObject(GameObject* parent, Transform transform);
		~GameObject();
		
		void Start();
		void Update();

		std::vector<Component*> GetComponents();

		template <class T>
		T* GetComponent();

		std::vector<GameObject*>& GetChildren();
		void SetParent(GameObject* newParent);
		std::string GetTag() const;
		void SetTag(const std::string newTag);

	protected:
		virtual void LoadComponents();
		void AddComponent(Component* newComponent);
	};


	template<class T>
	inline T* GameObject::GetComponent()
	{
		T temp();

		for (xe::Component* comp : components)
		{
			if (typeid(*comp).name() == typeid(temp).name()) return comp;
		}

		return nullptr;
	}
}

