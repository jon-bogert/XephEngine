#ifndef __XE_XEPHENGINE_WORLD_H__
#define __XE_XEPHENGINE_WORLD_H__

#include "GameObject.h"
#include "Service.h"

namespace xe
{
	class World final
	{
	public:
		void Initialize(uint32_t capacity);
		void Terminate();

		void Update(const float deltaTime);
		void Draw();
		void DebugUI();

		GameObject* CreateGameObject(const std::string& templatePath);
		GameObject* GetGameObject(const GameObjectHandle& handle);
		void DestroyGameObject(const GameObjectHandle& handle);

		void LoadLevel(const std::string levelFile);
		
		template <typename ServiceType>
		ServiceType* AddService()
		{
			static_assert(std::is_base_of_v<Service, ServiceType>, "World: service must be of type service");
			ASSERT(!m_initialized, "World: can't add service after world is initialized");
			auto& newService = m_services.emplace_back(std::make_unique<ServiceType>());
			newService->m_world = this;

			return static_cast<ServiceType*>(newService.get());
		}

		template <typename ServiceType>
		ServiceType* GetService()
		{
			for (auto& servicePtr : m_services)
			{
				if (servicePtr->GetTypeID() == ServiceType::StaticGetTypeID())
				{
					return static_cast<ServiceType*>(servicePtr.get());
				}
			}
			return nullptr;
		}

	private:
		bool IsValid(const GameObjectHandle& handle);
		void ProcessDestroyList();

		struct Slot
		{
			std::unique_ptr<GameObject> gameObject;
			uint32_t generation = 0;
		};

		using Services = std::vector<std::unique_ptr<Service>>;
		Services m_services;
		
		using GameObjectSlots = std::vector<Slot>;
		GameObjectSlots m_gameObjectSlots;
		std::vector<uint32_t> m_freeSlots;
		std::vector<uint32_t> m_slotsToDestroy;
		
		bool m_initialized = false;
		bool m_updating = false;
	};
}

#endif //!__XE_XEPHENGINE_WORLD_H__