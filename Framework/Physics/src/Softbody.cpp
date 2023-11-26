#include "Pch.h"
#include "Softbody.h"

#include "PhysicsWorld.h"

using namespace xe::Graphics;

xe::Physics::Softbody::~Softbody()
{
	ASSERT(_softbody == nullptr, "Softbody: terminate must be called");
}

void xe::Physics::Softbody::Initialize(Graphics::Mesh& mesh, float mass, const std::vector<int>& fixedNodeIndices)
{
	_mesh = &mesh;
	_softbody = PhysicsWorld::Get().CreateSoftbody(mesh.vertices.size());

	btSoftBody::Material* physMat = _softbody->appendMaterial();
	physMat->m_kAST = 1.f;
	_softbody->m_cfg.kMT = 0.2f;
	for (size_t i = 0; i < mesh.vertices.size(); ++i)
	{
		_softbody->m_nodes[i].m_x = mesh.vertices[i].position;
	}
	for (size_t i = 0; i < mesh.indices.size(); i += 6)
	{
		int index0 = mesh.indices[i];
		int index1 = mesh.indices[i + 4];
		int index2 = mesh.indices[i + 5];
		int index3 = mesh.indices[i + 2];

		_softbody->appendLink(index0, index1);
		_softbody->appendLink(index1, index2);
		_softbody->appendLink(index2, index3);
		_softbody->appendLink(index3, index1);
	}
	for (auto fixedNode : fixedNodeIndices)
	{
		_softbody->m_nodes[fixedNode].m_im = 0.f;
	}
	PhysicsWorld::Get().Register(this);
}

void xe::Physics::Softbody::Terminate()
{
	PhysicsWorld::Get().Unregister(this);
	SafeDelete(_softbody);
}

void xe::Physics::Softbody::Update(const float deltaTime)
{
	for (size_t i = 0; i < _mesh->vertices.size(); ++i)
	{
		_mesh->vertices[i].position = _softbody->m_nodes[i].m_x;
	}
}
