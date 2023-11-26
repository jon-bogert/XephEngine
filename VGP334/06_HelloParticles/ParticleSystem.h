#pragma once
#include "Particle.h"

struct ParticleSystemInfo
{
	ParticleInfo particleInfo;
	xe::Math::Vector3 spawnPosition;
	xe::Math::Vector3 spawnDirection;

	float spawnDelay;
	int minParticlesPerEmit = 0;
	int maxParticlesPerEmit = 0;
	float minTimeBetweenParticles = 0.f;
	float maxTimeBetweenParticles = 0.f;
	float minSpawnAngle = 0.f;
	float maxSpawnAngle = 0.f;
	float minSpeed = 0.f;
	float maxSpeed = 0.f;
	float lifeTime = 0.f;
	int maxParticles = 0;
};

class ParticleSystem
{
	void SpawnParticles();
	void SpawnParticle();

	using Particles = std::vector<Particle>;
	Particles _particles;

	ParticleSystemInfo _info;

	int _nextAvailableParticleIndex;
	float _nextSpawn = 0.f;
	float _time = 0.f;

public:
	ParticleSystem() = default;
	~ParticleSystem() = default;

	void Initialize(const ParticleSystemInfo& info);
	void Terminate();
	void Update(const float deltaTime);
	void DebugUI();

	template <class Effect>
	void Draw(Effect& effect)
	{
		if (_time > 0.f)
		{
			for (auto& particle : _particles)
			{
				particle.Draw(effect);
			}
		}
	}
};