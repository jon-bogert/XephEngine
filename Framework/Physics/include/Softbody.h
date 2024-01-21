#ifndef __XE_PHYSICS_SOFTBODY_H__
#define __XE_PHYSICS_SOFTBODY_H__

#include "PhysicsObject.h"
#include <Graphics/include/MeshTypes.h>

namespace xe::Physics
{
	class Softbody final : public PhysicsObject
	{
		btSoftBody* _softbody = nullptr;
		Graphics::Mesh* _mesh = nullptr;

	public:
		Softbody() = default;
		~Softbody();

		void Initialize(Graphics::Mesh& mesh, float mass, const std::vector<int>& fixedNodeIndices);
		void Terminate();

		void Update(const float deltaTime) override;
		btSoftBody* GetSoftbody() override { return _softbody; }
	};
}

#endif // __XE_PHYSICS_SOFTBODY_H__
