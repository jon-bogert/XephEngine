#ifndef __XE_XEPHENGINE_RIGIDBODYCOMPONENT_H__
#define __XE_XEPHENGINE_RIGIDBODYCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class RigidbodyComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Rigidbody);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const yaml_val& data) override;

		void SetPosition(const xe::Math::Vector3& position);

	private:
		friend class PhysicsService;
		Physics::Rigidbody m_rigidbody;
		float m_mass = 1.f;
	};
}

#endif //!__XE_XEPHENGINE_RIGIDBODYCOMPONENT_H__
