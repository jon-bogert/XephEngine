#ifndef __XE_PHYSICS_PHYSICSDEBUGDRAWER_H__
#define __XE_PHYSICS_PHYSICSDEBUGDRAWER_H__

namespace xe::Physics
{
	namespace Impl
	{
		class _PhysicsDebugDrawer final : public btIDebugDraw
		{
			int _debugMode = 0;

		public:
			void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
			void drawContactPoint(const btVector3& pointOn, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
			void reportErrorWarning(const char* warningString) override;
			void draw3dText(const btVector3& location, const char* textString) override;
			void setDebugMode(int debugMode) override;
			int getDebugMode() const override;
		};
	}

	class PhysicsDebugDrawer final
	{
	public:
		void DrawLine(const btVector3& from, const btVector3& to, const btVector3& color) { _drawer.drawLine(from, to, color); }
		void ReportErrorWarning(const char* warningString) { _drawer.reportErrorWarning(warningString); }
		void SetDebugMode(int debugMode) { _drawer.setDebugMode(debugMode); }
		int GetDebugMode() const { return _drawer.getDebugMode(); }

	private:
		Impl::_PhysicsDebugDrawer _drawer;
	};
}

#endif // __XE_PHYSICS_PHYSICSDEBUGDRAWER_H__
