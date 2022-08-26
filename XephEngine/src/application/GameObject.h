#pragma once
#include "../../lib/XephEngine/Engine.h"

namespace xe
{

	class Component;
	class GameObject;
	struct Transform;

	class GameObject
	{
	protected:
		std::string tag{};
		std::vector<Component*> components{};
		GameObject* parent = nullptr;
		std::vector<GameObject*> children{};
		bool isActive = true;

		void Awake();

	public:
		Transform transform{};
		GameObject();
		GameObject(GameObject* parent);
		GameObject(Transform tranform);
		GameObject(GameObject* parent, Transform transform);
		~GameObject();
		
		void Start();
		void Update();
		void OnDestroy();

		bool GetIsActive() const;
		void SetIsActive(const bool setTo);

		void OnCollision(GameObject* other);
		void OnTrigger(GameObject* other);

		std::vector<Component*> GetComponents();

		template <class T>
		T* GetComponent(); // TODO Test and Fix

		std::vector<GameObject*>& GetChildren();
		void SetParent(GameObject* newParent);
		std::string GetTag() const;
		void SetTag(const std::string newTag);


	protected:
		virtual void LoadComponents();
		Component* AddComponent(Component* newComponent);
	};


	template<class T>
	inline T* GameObject::GetComponent()
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
		for (xe::Component* comp : components)
		{
			if (typeid(*comp).name() == proc) return (T*)comp;
		}
		return nullptr;
	}
}

