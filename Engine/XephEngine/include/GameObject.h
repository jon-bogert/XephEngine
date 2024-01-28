#ifndef __XE_XEPHENGINE_GAMEOBJECT_H__
#define __XE_XEPHENGINE_GAMEOBJECT_H__

#include "Component.h"
#include "GameObjectHandle.h"

namespace xe
{
	class GameObject final
	{
	public:
		void Initialize();
		void Terminate();

		void DebugUI();

		void SetName(const std::string& name) { m_name = std::move(name); }
		const std::string& GetName() const { return m_name; }
		uint32_t GetGUID() const { return m_guid; }

		World& GetWorld() { return *m_world; }
		const World& GetWorld() const { return *m_world; }
		const GameObjectHandle& GetHandle() const { return m_handle; }

		template<typename ComponentType>
		ComponentType* AddComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "GameObject ->  Component type must be of type component");
			ASSERT(!m_initialized, "GameObject -> cannot add components once initialized");
			ASSERT(!HasComponent<ComponentType>(), "GameObject -> already has this component type");
			auto& newComponent = m_components.emplace_back(std::make_unique<ComponentType>());
			newComponent->m_gameObject = this;
			return static_cast<ComponentType*>(newComponent.get());
		}

		template <typename ComponentType>
		bool HasComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "GameObject -> Component Type must be of type Component");

			for (auto& component : m_components)
			{
				if (component->GetTypeID() == ComponentType::StaticGetTypeID())
				{
					return true;
				}
			}
			return false;
		}

		template <typename ComponentType>
		ComponentType* GetComponent()
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "GameObject -> Component Type must be of type Component");

			for (auto& component : m_components)
			{
				if (component->GetTypeID() == ComponentType::StaticGetTypeID())
				{
					return static_cast<ComponentType*>(component.get());
				}
			}
			return nullptr;
		}

		template <typename ComponentType>
		const ComponentType* GetComponent() const
		{
			static_assert(std::is_base_of_v<Component, ComponentType>, "GameObject -> Component Type must be of type Component");

			for (auto& component : m_components)
			{
				if (component->GetTypeID() == ComponentType::StaticGetTypeID())
				{
					return static_cast<ComponentType*>(component.get());
				}
			}
			return nullptr;
		}

	private:
		friend class World;
		World* m_world = nullptr;
		GameObjectHandle m_handle;

		std::string m_name = "GameObject";
		bool m_initialized = false;
		uint32_t m_guid = NULL;

		using Components = std::vector<std::unique_ptr<Component>>;
		Components m_components;
	};
}

#endif //!__XE_XEPHENGINE_GAMEOBJECT_H__