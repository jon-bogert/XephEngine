#ifndef __XE_PHYSICS_PHYSICSWORLD_H__
#define __XE_PHYSICS_PHYSICSWORLD_H__

#include "PhysicsDebugDrawer.h"

namespace xe::Physics
{
	class PhysicsObject;
	class PhysicsWorld final
	{
	public:
		struct Settings
		{
			xe::Math::Vector3 gravity = { 0.f, -9.81f, 0.f };
			uint32_t simulationSteps = 1;
			float fixedTimeStep = 1.f / 60.f;
		};

		static void Initialize(const Settings& settings);
		static void Terminate();
		static PhysicsWorld& Get();

		PhysicsWorld() = default;
		~PhysicsWorld();

		static void Update(const float deltaTime);
		static void DebugUI();

		void Register(PhysicsObject* physObj);
		void Unregister(PhysicsObject* physObj);


	private:
		void _Initialize(const Settings& settings);
		void _Terminate();
		void _Update(const float deltaTime);
		void _DebugUI();

		Settings m_settings;
		bool m_renderDebugUI = false;

		PhysicsDebugDrawer m_debugDrawer;

		//Bullet objects
		btBroadphaseInterface* m_interface = nullptr;
		btCollisionDispatcher* m_dispatcher = nullptr;
		btDefaultCollisionConfiguration* m_collisionConfiguration = nullptr;
		btDiscreteDynamicsWorld* m_dynamicWorld = nullptr;
		btSequentialImpulseConstraintSolver* m_solver = nullptr;

		//For Soft Bodies
		btSoftRigidDynamicsWorld* m_softbodyWorld = nullptr;
		friend class Softbody;
		btSoftBody* CreateSoftbody(int nodeCount);

		using PhysicsObjects = std::vector<PhysicsObject*>;
		PhysicsObjects m_physicsObjects;
	};
}

#endif //!__XE_PHYSICS_PHYSICSWORLD_H__
