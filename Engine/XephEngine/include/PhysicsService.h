#ifndef __XE_XEPHENGINE_PHYISICSSERVICE_H__
#define __XE_XEPHENGINE_PHYISICSSERVICE_H__

#include "Service.h"

namespace xe
{
	class RigidbodyComponent;
	class PhysicsService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceID::Physics);

		void Update(const float deltaTime) override;
		void DebugUI() override;

		void Deserialize(const yaml_val& data) override;

		void Register(RigidbodyComponent& rigidbodyComponent);
		void Unregister(RigidbodyComponent& rigidbodyComponent);

	private:
	};
}

#endif //!__XE_XEPHENGINE_PHYISICSSERVICE_H__
