#include "Pch.h"
#include "Rigidbody.h"

#include "CollisionShape.h"
#include "PhysicsWorld.h"

xe::Physics::Rigidbody::~Rigidbody()
{
	ASSERT(_rigidbody == nullptr, "Rigidbody: terminate must be called");
}

void xe::Physics::Rigidbody::Initialize(xe::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	_graphicsTransform = &graphicsTransform;
	_mass = mass;

	_motionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	_rigidbody = new btRigidBody(_mass, _motionState, shape.GetCollisionShape());
	_rigidbody->setRestitution(0.5f);

	PhysicsWorld::Get().Register(this);
}

void xe::Physics::Rigidbody::Terminate()
{
	PhysicsWorld::Get().Unregister(this);
	SafeDelete(_motionState);
	SafeDelete(_rigidbody);
	_graphicsTransform = nullptr;
}

void xe::Physics::Rigidbody::SetPosition(xe::Math::Vector3 position)
{
	_graphicsTransform->position = position;
	_rigidbody->setWorldTransform(ConvertTobtTransform(*_graphicsTransform));
}

void xe::Physics::Rigidbody::SetVelocity(xe::Math::Vector3 velocity)
{
	_rigidbody->activate();
	_rigidbody->setLinearVelocity(velocity);
}

bool xe::Physics::Rigidbody::IsDynamic() const
{
	return _mass > 0.f;
}

void xe::Physics::Rigidbody::Update(const float deltaTime)
{
	btTransform worldTransform = _rigidbody->getWorldTransform();
	_graphicsTransform->position = worldTransform.getOrigin();
	_graphicsTransform->rotation = worldTransform.getRotation();
}
