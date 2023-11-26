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
		btRigidBody* GetRigidbody() override { return _rigidbody; }

		btRigidBody* _rigidbody = nullptr;
		btDefaultMotionState* _motionState = nullptr;
		float _mass = 0.f;
		
		xe::Graphics::Transform* _graphicsTransform = nullptr;

	public:
		Rigidbody() = default;
		~Rigidbody() override;

		void Initialize(xe::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass = 0.f);
		void Terminate();

		void SetPosition(xe::Math::Vector3 position);
		void SetVelocity(xe::Math::Vector3 velocity);

		bool IsDynamic() const;

		void Update(const float deltaTime) override;
	};
}

#endif // __XE_PHYSICS_RIGIDBODY_H__

