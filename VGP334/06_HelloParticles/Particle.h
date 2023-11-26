#pragma once

#include <XephEngine/include/XephEngine.h>

struct ParticleInfo
{
	float lifetime = 0.f;
	xe::Color colorStart = xe::Colors::White;
	xe::Color colorEnd = xe::Colors::White;
	xe::Math::Vector3 scaleStart = xe::Math::Vector3::One;
	xe::Math::Vector3 scaleEnd = xe::Math::Vector3::One;
};

class Particle
{
	xe::Graphics::RenderObject _particle;
	xe::Graphics::MeshPC _mesh;
	xe::Physics::Rigidbody _rigidbody;
	xe::Physics::CollisionShape _shape;

	bool _isActive = false;
	ParticleInfo _info;

	float _time = 0.f;
	float _lifeTime = 0.f;

public:
	Particle() = default;
	
	void Initialize();
	void Terminate();

	void Activate(const ParticleInfo& info, const xe::Math::Vector3& pos, const xe::Math::Vector3& vel);
	void Update(const float deltaTime);

	template <class Effect>
	void Draw(Effect& effect)
	{
		if (!_isActive)
			return;

		effect.Draw(_particle);
	}
};