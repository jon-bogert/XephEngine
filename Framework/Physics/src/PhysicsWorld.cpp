#include "Pch.h"
#include "PhysicsWorld.h"

#include "PhysicsObject.h"

namespace
{
	std::unique_ptr<xe::Physics::PhysicsWorld> physicsWorld = nullptr;
}

void xe::Physics::PhysicsWorld::Initialize(const Settings& settings)
{
	ASSERT(physicsWorld == nullptr, "PhysicsWorld : is already initialized");
	physicsWorld = std::make_unique<PhysicsWorld>();
	physicsWorld->_Initialize(settings);
}

void xe::Physics::PhysicsWorld::Terminate()
{
	if (physicsWorld != nullptr)
	{
		physicsWorld->_Terminate();
		physicsWorld.reset();
	}
}

xe::Physics::PhysicsWorld& xe::Physics::PhysicsWorld::Get()
{
	ASSERT(physicsWorld != nullptr, "PhysicsWorld: must be initialized");
	return *physicsWorld;
}

xe::Physics::PhysicsWorld::~PhysicsWorld()
{
	ASSERT(physicsWorld == nullptr, "PhysicsWorld: must be terminated");
}

void xe::Physics::PhysicsWorld::Update(float deltaTime)
{
	physicsWorld->_Update(deltaTime);
}

void xe::Physics::PhysicsWorld::DebugUI()
{
	physicsWorld->_DebugUI();
}

void xe::Physics::PhysicsWorld::Register(PhysicsObject* physObj)
{
	if (std::find(m_physicsObjects.begin(), m_physicsObjects.end(), physObj) != m_physicsObjects.end())
	{
		ASSERT(false, "PhysicsWorld::Register -> object already added");
		return;
	}

	m_physicsObjects.push_back(physObj);
	if (physObj->GetRigidbody() != nullptr)
	{
		m_dynamicWorld->addRigidBody(physObj->GetRigidbody());
	}
	if (physObj->GetSoftbody() != nullptr)
	{
		m_softbodyWorld->addSoftBody(physObj->GetSoftbody());
	}
}

void xe::Physics::PhysicsWorld::Unregister(PhysicsObject* physObj)
{
	auto iter = std::find(m_physicsObjects.begin(), m_physicsObjects.end(), physObj);
	if (iter != m_physicsObjects.end())
	{
		if (physObj->GetRigidbody() != nullptr)
		{
			m_dynamicWorld->removeRigidBody(physObj->GetRigidbody());
		}
		if (physObj->GetSoftbody() != nullptr)
		{
			m_softbodyWorld->removeSoftBody(physObj->GetSoftbody());
		}
		m_physicsObjects.erase(iter);
	}
}

void xe::Physics::PhysicsWorld::_Initialize(const Settings& settings)
{
	m_settings = settings;
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_interface = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver();
	m_dynamicWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_interface, m_solver, m_collisionConfiguration);
	m_dynamicWorld->setGravity(settings.gravity);
	m_dynamicWorld->setDebugDrawer(m_debugDrawer.Unwrap());

	m_softbodyWorld = new btSoftRigidDynamicsWorld(m_dispatcher, m_interface, m_solver, m_collisionConfiguration);
	m_softbodyWorld->setGravity(settings.gravity);
	m_softbodyWorld->setDebugDrawer(m_debugDrawer.Unwrap());
}

void xe::Physics::PhysicsWorld::_Terminate()
{
	SafeDelete(m_softbodyWorld);
	SafeDelete(m_dynamicWorld);
	SafeDelete(m_solver);
	SafeDelete(m_interface);
	SafeDelete(m_dispatcher);
	SafeDelete(m_collisionConfiguration);
}

void xe::Physics::PhysicsWorld::_Update(const float deltaTime)
{
	m_dynamicWorld->stepSimulation(deltaTime, m_settings.simulationSteps, m_settings.fixedTimeStep);
	m_softbodyWorld->stepSimulation(deltaTime, m_settings.simulationSteps, m_settings.fixedTimeStep);
	for (PhysicsObject* obj : m_physicsObjects)
	{
		obj->Update(deltaTime);
	}
}

void xe::Physics::PhysicsWorld::_DebugUI()
{
	ImGui::Checkbox("Render Physics", &m_renderDebugUI);
	if (m_renderDebugUI)
	{
		int debugMode = m_debugDrawer.GetDebugMode();
		bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;
		if (ImGui::Checkbox("[DGB]DrawWireframe", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
		}
		isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb) > 0;
		if (ImGui::Checkbox("[DBG]DrawAABB", &isEnabled))
		{
			debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
		}
		m_debugDrawer.SetDebugMode(debugMode);
		m_dynamicWorld->debugDrawWorld();
		m_softbodyWorld->debugDrawWorld();
	}
}

btSoftBody* xe::Physics::PhysicsWorld::CreateSoftbody(int nodeCount)
{
	btSoftBody* softbody = new btSoftBody(&m_softbodyWorld->getWorldInfo(), nodeCount, nullptr, nullptr);
	return softbody;
}
