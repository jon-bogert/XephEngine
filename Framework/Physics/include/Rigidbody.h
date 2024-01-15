#ifndef __XE_PHYSICS_RIGIDBODY_H__
#define __XE_PHYSICS_RIGIDBODY_H__

#include "PhysicsObject.h"

namespace xe::Graphics
{
	struct Transform;
}
namespace xe::Physics
{
	class CollisionShape;
	class Rigidbody final : public PhysicsObject
	{
	public:
		Rigidbody() = default;
		~Rigidbody() override;

		void Initialize(xe::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.f);
		void Terminate();

		void SetPosition(xe::Math::Vector3 position);
		void SetVelocity(xe::Math::Vector3 velocity);

		bool IsDynamic() const;

		void Update(const float deltaTime) override;

	private:
		btRigidBody* GetRigidbody() override { return m_rigidbody; }

		btRigidBody* m_rigidbody = nullptr;
		btDefaultMotionState* m_motionState = nullptr;
		float m_mass = 0.f;

		xe::Graphics::Transform* m_graphicsTransform = nullptr;
	};
}

#endif //!__XE_PHYSICS_RIGIDBODY_H__

