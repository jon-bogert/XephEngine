#ifndef __XE_PHYSICS_PHYSICSOBJECT_H__
#define __XE_PHYSICS_PHYSICSOBJECT_H__

class btRigidBody;

namespace xe::Physics
{
	class PhysicsObject
	{
	friend class PhysicsWorld;
	public:
		PhysicsObject() = default;
		virtual ~PhysicsObject() = default;

	private:
		virtual void Update(const float deltaTime) = 0;
		virtual btRigidBody* GetRigidbody() { return nullptr; }
		virtual btSoftBody* GetSoftbody() { return nullptr; }
	};
}

#endif // __XE_PHYSICS_PHYSICSOBJECT_H__