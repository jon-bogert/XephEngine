#ifndef __XE_XEPHENGINE_UPDATESERVICE_H__
#define __XE_XEPHENGINE_UPDATESERVICE_H__

#include "Service.h"

namespace xe
{
	class Component;
	class UpdateService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceID::Update);

		void Update(const float deltaTime) override;

		void Register(Component* component);
		void Unregister(Component* component);

	private:
		using UpdateComponents = std::vector<Component*>;
		UpdateComponents m_updateComponents;
		UpdateComponents m_pendingUpdateComponents;

		void RegisterPendingUpdates();

		bool m_isUpdating = false;
	};
}

#endif //!__XE_XEPHENGINE_UPDATESERVICE_H__
