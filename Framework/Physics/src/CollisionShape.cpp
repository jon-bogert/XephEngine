#include "Pch.h"
#include "CollisionShape.h"

namespace xe::Physics
{
	CollisionShape::~CollisionShape()
	{
		ASSERT(_collisionShape == nullptr, "CollisionShape: must call terminate");
	}
	void CollisionShape::InitializeSphere(float radius)
	{
		ASSERT(_collisionShape == nullptr, "CollisionShape: is already initialized");
		_collisionShape = new btSphereShape(radius);
	}
	void CollisionShape::InitializeBox(const xe::Math::Vector3& halfExtends)
	{
		ASSERT(_collisionShape == nullptr, "CollisionShape: is already initialized");
		_collisionShape = new btBoxShape(halfExtends);
	}
	void CollisionShape::InitializeHull(const xe::Math::Vector3& halfExtends, const xe::Math::Vector3& origin)
	{
		ASSERT(_collisionShape == nullptr, "CollisionShape: is already initialized");
		btConvexHullShape* hullShape = new btConvexHullShape();
		std::vector<xe::Math::Vector3> points
		{
			{-halfExtends.x, -halfExtends.y, -halfExtends.z },
			{ -halfExtends.x, halfExtends.y, -halfExtends.z },
			{ halfExtends.x, halfExtends.y, -halfExtends.z },
			{ halfExtends.x, -halfExtends.y, -halfExtends.z },
			{ -halfExtends.x, -halfExtends.y, halfExtends.z },
			{ -halfExtends.x, halfExtends.y, halfExtends.z },
			{ halfExtends.x, halfExtends.y, halfExtends.z },
			{ halfExtends.x, -halfExtends.y, halfExtends.z }
		};

		for (xe::Math::Vector3& point : points)
		{
			hullShape->addPoint(point + origin, false);
		}
		hullShape->recalcLocalAabb();
		_collisionShape = hullShape;
	}

	void CollisionShape::InitializeEmpty()
	{
		ASSERT(_collisionShape == nullptr, "CollisionShape: is already initialized");
		_collisionShape = new btEmptyShape();
	}
	void CollisionShape::Termainate()
	{
		SafeDelete(_collisionShape);
	}
}