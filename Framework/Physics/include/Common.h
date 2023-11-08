#ifndef __XE_PHYSICS_COMMON_H__
#define __XE_PHYSICS_COMMON_H__

//Framework
#include <Math/include/XEMath.h>
#include <Core/include/Core.h>
#include <Graphics/include/Transform.h>

//Bullet

#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

template<class T>
inline void SafeDelete(T* ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

#endif // __XE_PHYSICS_COMMON_H__