#include "Pch.h"
#include "RigidbodyComponent.h"

#include "World.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "PhysicsService.h"

void xe::RigidbodyComponent::Initialize()
{
	ColliderComponent* collider = GetGameObject().GetComponent<ColliderComponent>();
	TransformComponent* transform = GetGameObject().GetComponent<TransformComponent>();
	ASSERT(collider != nullptr, "RigidbodyComponent: requires ColliderComponent on GameObject");

	m_rigidbody.Initialize(*transform, collider->m_collisionShape, m_mass);

	PhysicsService* physicsService = GetGameObject().GetWorld().GetService<PhysicsService>();
	physicsService->Register(*this);
}

void xe::RigidbodyComponent::Terminate()
{
	PhysicsService* physicsService = GetGameObject().GetWorld().GetService<PhysicsService>();
	physicsService->Unregister(*this);
	m_rigidbody.Terminate();
}

void xe::RigidbodyComponent::Serialize(YAML::Node& data)
{
	data["type"] = "RigidbodyComponent";
	data["mass"] = m_mass;
}

void xe::RigidbodyComponent::Deserialize(const yaml_val& data)
{
	m_mass = data["mass"].as<float>();
}

void xe::RigidbodyComponent::SetPosition(const xe::Math::Vector3& position)
{
	m_rigidbody.SetPosition(position);
}
