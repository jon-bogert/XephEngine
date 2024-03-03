#include "Pch.h"
#include "PhysicsService.h"

#include "RigidbodyComponent.h"

using namespace xe::Physics;
using namespace xe::Math;

void xe::PhysicsService::Update(const float deltaTime)
{
	PhysicsWorld::Get().Update(deltaTime);
}

void xe::PhysicsService::DebugUI()
{
	PhysicsWorld::Get().DebugUI();
}

void xe::PhysicsService::Deserialize(const yaml_val& data)
{
	Vector3 gravity;
	gravity.x = data["gravity"]["x"].as<float>();
	gravity.y = data["gravity"]["y"].as<float>();
	gravity.z = data["gravity"]["z"].as<float>();
	PhysicsWorld::SetGravity(gravity);

	uint32_t steps = data["steps"].as<uint32_t>();
	PhysicsWorld::SetSimulationSteps(steps);

	float timeStep = data["time-step"].as<float>();
	PhysicsWorld::SetFixedTimeStep(timeStep);
}

void xe::PhysicsService::Register(RigidbodyComponent& rigidbodyComponent)
{
	PhysicsWorld::Get().Register(&rigidbodyComponent.m_rigidbody);
}

void xe::PhysicsService::Unregister(RigidbodyComponent& rigidbodyComponent)
{
	PhysicsWorld::Get().Unregister(&rigidbodyComponent.m_rigidbody);
}

void xe::PhysicsService::SetEnabled(bool enabled)
{
	PhysicsWorld::SetEnabled(enabled);
}
