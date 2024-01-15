#include "Pch.h"
#include "PhysicsDebugDrawer.h"

#include <Graphics/include/Colors.h>
#include <Graphics/include/SimpleDraw.h>

using namespace xe::Graphics;
using namespace xe::Physics;

void xe::Physics::Impl::_PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	SimpleDraw::AddLine(from, to, Color(color.x(), color.y(), color.z(), 1.f));
}

void xe::Physics::Impl::_PhysicsDebugDrawer::drawContactPoint(const btVector3& pointOn, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	//NOTHING HERE
}

void xe::Physics::Impl::_PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{
	LOG("[Physics Warning] %s", warningString);
}

void xe::Physics::Impl::_PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	//NOTHING HERE
}

void xe::Physics::Impl::_PhysicsDebugDrawer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;
}

int xe::Physics::Impl::_PhysicsDebugDrawer::getDebugMode() const
{
	return m_debugMode;
}
