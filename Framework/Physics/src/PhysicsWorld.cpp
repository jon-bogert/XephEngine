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

void xe::Physics::PhysicsWorld::SetGravity(const xe::Math::Vector3& gravity)
{
	physicsWorld->_settings.gravity = gravity;
	if (physicsWorld->_dynamicWorld != nullptr)
	{
		physicsWorld->_dynamicWorld->setGravity(gravity);
	}
	if (physicsWorld->_softbodyWorld != nullptr)
	{
		physicsWorld->_softbodyWorld->setGravity(gravity);
	}
}
void xe::Physics::PhysicsWorld::SetSimulationSteps(const uint32_t steps)
{
	physicsWorld->_settings.simulationSteps = steps;
}
void xe::Physics::PhysicsWorld::SetFixedTimeStep(const float timeStep)
{
	physicsWorld->_settings.fixedTimeStep = timeStep;
}

void xe::Physics::PhysicsWorld::Register(PhysicsObject* physObj)
{
	if (std::find(_physicsObjects.begin(), _physicsObjects.end(), physObj) != _physicsObjects.end())
	{
		ASSERT(false, "PhysicsWorld::Register -> object already added");
		return;
	}

	_physicsObjects.push_back(physObj);
	if (physObj->GetRigidbody() != nullptr)
	{
		_dynamicWorld->addRigidBody(physObj->GetRigidbody());
	}
	if (physObj->GetSoftbody() != nullptr)
	{
		_softbodyWorld->addSoftBody(physObj->GetSoftbody());
	}
}

void xe::Physics::PhysicsWorld::Unregister(PhysicsObject* physObj)
{
	auto iter = std::find(_physicsObjects.begin(), _physicsObjects.end(), physObj);
	if (iter != _physicsObjects.end())
	{
		if (physObj->GetRigidbody() != nullptr)
		{
			_dynamicWorld->removeRigidBody(physObj->GetRigidbody());
		}
		if (physObj->GetSoftbody() != nullptr)
		{
			_softbodyWorld->removeSoftBody(physObj->GetSoftbody());
		}
		_physicsObjects.erase(iter);
	}
}

void xe::Physics::PhysicsWorld::_Initialize(const Settings& settings)
{
	_settings = settings;
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	_interface = new btDbvtBroadphase();
	_solver = new btSequentialImpulseConstraintSolver();
	_dynamicWorld = new btDiscreteDynamicsWorld(_dispatcher, _interface, _solver, _collisionConfiguration);
	_dynamicWorld->setGravity(settings.gravity);
	_dynamicWorld->setDebugDrawer(_debugDrawer.Unwrap());

	_softbodyWorld = new btSoftRigidDynamicsWorld(_dispatcher, _interface, _solver, _collisionConfiguration);
	_softbodyWorld->setGravity(settings.gravity);
	_softbodyWorld->setDebugDrawer(_debugDrawer.Unwrap());
}

void xe::Physics::PhysicsWorld::_Terminate()
{
	SafeDelete(_softbodyWorld);
	SafeDelete(_dynamicWorld);
	SafeDelete(_solver);
	SafeDelete(_interface);
	SafeDelete(_dispatcher);
	SafeDelete(_collisionConfiguration);
}

void xe::Physics::PhysicsWorld::_Update(const float deltaTime)
{
	_dynamicWorld->stepSimulation(deltaTime, _settings.simulationSteps, _settings.fixedTimeStep);
	//_softbodyWorld->stepSimulation(deltaTime, _settings.simulationSteps, _settings.fixedTimeStep);
	for (PhysicsObject* obj : _physicsObjects)
	{
		obj->Update(deltaTime);
	}
}

void xe::Physics::PhysicsWorld::_DebugUI()
{
	ImGui::Checkbox("Render Physics", &_renderDebugUI);
	if (_renderDebugUI)
	{
		int debugMode = _debugDrawer.GetDebugMode();
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
		_debugDrawer.SetDebugMode(debugMode);
		_dynamicWorld->debugDrawWorld();
		_softbodyWorld->debugDrawWorld();
	}
}

btSoftBody* xe::Physics::PhysicsWorld::CreateSoftbody(int nodeCount)
{
	btSoftBody* softbody = new btSoftBody(&_softbodyWorld->getWorldInfo(), nodeCount, nullptr, nullptr);
	return softbody;
}
