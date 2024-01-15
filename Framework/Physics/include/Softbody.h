#ifndef __XE_PHYSICS_SOFTBODY_H__
#define __XE_PHYSICS_SOFTBODY_H__

#include "PhysicsObject.h"
#include <Graphics/include/MeshTypes.h>

namespace xe::Physics
{
	class Softbody final : public PhysicsObject
	{
	public:
		Softbody() = default;
		~Softbody();

		void Initialize(Graphics::Mesh& mesh, float mass, const std::vector<int>& fixedNodeIndices);
		void Terminate();

		void Update(const float deltaTime) override;
		btSoftBody* GetSoftbody() override { return m_softbody; }

	private:
		btSoftBody* m_softbody = nullptr;
		Graphics::Mesh* m_mesh = nullptr;
	};
}

#endif //!__XE_PHYSICS_SOFTBODY_H__
