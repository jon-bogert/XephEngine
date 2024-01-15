#include "Pch.h"
#include "Rigidbody.h"

#include "CollisionShape.h"
#include "PhysicsWorld.h"

xe::Physics::Rigidbody::~Rigidbody()
{
	ASSERT(m_rigidbody == nullptr, "Rigidbody: terminate must be called");
}

void xe::Physics::Rigidbody::Initialize(xe::Graphics::Transform& graphicsTransform, const CollisionShape& shape, float mass)
{
	m_graphicsTransform = &graphicsTransform;
	m_mass = mass;

	m_motionState = new btDefaultMotionState(ConvertTobtTransform(graphicsTransform));
	m_rigidbody = new btRigidBody(m_mass, m_motionState, shape.GetCollisionShape());
	m_rigidbody->setRestitution(0.5f);

	PhysicsWorld::Get().Register(this);
}

void xe::Physics::Rigidbody::Terminate()
{
	PhysicsWorld::Get().Unregister(this);
	SafeDelete(m_motionState);
	SafeDelete(m_rigidbody);
	m_graphicsTransform = nullptr;
}

void xe::Physics::Rigidbody::SetPosition(xe::Math::Vector3 position)
{
	m_graphicsTransform->position = position;
	m_rigidbody->setWorldTransform(ConvertTobtTransform(*m_graphicsTransform));
}

void xe::Physics::Rigidbody::SetVelocity(xe::Math::Vector3 velocity)
{
	m_rigidbody->activate();
	m_rigidbody->setLinearVelocity(velocity);
}

bool xe::Physics::Rigidbody::IsDynamic() const
{
	return m_mass > 0.f;
}

void xe::Physics::Rigidbody::Update(const float deltaTime)
{
	btTransform worldTransform = m_rigidbody->getWorldTransform();
	m_graphicsTransform->position = worldTransform.getOrigin();
	m_graphicsTransform->rotation = worldTransform.getRotation();
}
