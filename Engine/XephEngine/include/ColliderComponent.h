#ifndef __XE_XEPHENGINE_COLLIDERCOMPONENT_H__
#define __XE_XEPHENGINE_COLLIDERCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class ColliderComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Collider);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const yaml_val& data) override;

	private:
		friend class RigidbodyComponent;
		Physics::CollisionShape m_collisionShape;
	};
}

#endif //__XE_XEPHENGINE_COLLIDERCOMPONENT_H__
