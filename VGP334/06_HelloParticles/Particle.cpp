#include "Particle.h"

using namespace xe::Graphics;
using namespace xe::Physics;
using namespace xe::Math;
using namespace xe;

void Particle::Initialize()
{
	_isActive = false;
	_time = 0.f;
	_lifeTime = 0.f;

	_mesh = MeshBuilder::CreateUVSpherePC(10, 10, 0.5f);
	_particle.meshBuffer.Initialize(nullptr, sizeof(VertexPC), _mesh.vertices.size(), _mesh.indices.data(), _mesh.indices.size());
	_shape.InitializeEmpty();
	_rigidbody.Initialize(_particle.transform, _shape, 0.1f);
}

void Particle::Terminate()
{
	_rigidbody.Terminate();
	_shape.Termainate();
	_particle.Terminate();
}

void Particle::Activate(const ParticleInfo& info, const xe::Math::Vector3& pos, const xe::Math::Vector3& vel)
{
	_time = 0.f;
	_lifeTime = info.lifetime;
	_isActive = true;
	_info = info;
	_rigidbody.SetPosition(pos);
	_rigidbody.SetVelocity(vel);
}

void Particle::Update(const float deltaTime)
{
	if (_isActive)
	{
		_time += deltaTime;
		float t = Clamp(_time / _lifeTime, 0.f, 1.f);

		Color currentColor = Lerp(_info.colorStart, _info.colorEnd, t);
		_particle.transform.scale = Lerp(_info.scaleStart, _info.scaleEnd, t);
		for (uint32_t i = 0; i < _mesh.vertices.size(); ++i)
		{
			_mesh.vertices[i].color = currentColor;
		}
		_particle.meshBuffer.Update(_mesh.vertices.data(), _mesh.vertices.size());
	}
}
