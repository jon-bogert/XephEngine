#ifndef __XE_PHYSICS_COLLISIONSHAPE_H__
#define __XE_PHYSICS_COLLISIONSHAPE_H__
namespace xe::Physics
{
	class CollisionShape final
	{
		friend class Rigidbody;

	public:
		CollisionShape() = default;
		~CollisionShape();

		void InitializeSphere(float radius);
		void InitializeBox(const xe::Math::Vector3& halfExtends);
		void InitializeHull(const xe::Math::Vector3& halfExtends, const xe::Math::Vector3& origin);
		void InitializeEmpty();
		void Termainate();

	private:
		btCollisionShape* m_collisionShape = nullptr;
		btCollisionShape* GetCollisionShape() const { return m_collisionShape; }
	};
}
#endif //!__XE_PHYSICS_COLLISIONSHAPE_H__