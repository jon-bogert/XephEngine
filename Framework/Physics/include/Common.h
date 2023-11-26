#ifndef __XE_PHYSICS_COMMON_H__
#define __XE_PHYSICS_COMMON_H__

//Framework
#include <Math/include/XEMath.h>
#include <Core/include/Core.h>
#include <Graphics/include/Transform.h>

//Bullet

#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>
#include <Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h>
#include <Bullet/BulletSoftBody/btSoftBodyHelpers.h>
#include <Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h>
#include <Bullet/BulletSoftBody/btSoftBodySolvers.h>

template<class T>
inline void SafeDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

inline btTransform ConvertTobtTransform(const xe::Graphics::Transform& transform)
{
	return btTransform(transform.rotation, transform.position);
}

#endif // __XE_PHYSICS_COMMON_H__