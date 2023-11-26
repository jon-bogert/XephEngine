#include "ParticleSystem.h"

using namespace xe::Graphics;
using namespace xe::Physics;
using namespace xe::Math;
using namespace xe;

void ParticleSystem::SpawnParticles()
{
	int numParticles = _info.minParticlesPerEmit + (rand() % _info.maxParticlesPerEmit - _info.minParticlesPerEmit);
	for (uint32_t i = 0; i < numParticles; ++i)
	{
		SpawnParticle();
	}
	float randFloat = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
	_nextSpawn = _info.minTimeBetweenParticles + ((_info.maxTimeBetweenParticles - _info.minTimeBetweenParticles) * randFloat);
}

void ParticleSystem::SpawnParticle()
{
	Particle& p = _particles[_nextAvailableParticleIndex];
	_nextAvailableParticleIndex = (_nextAvailableParticleIndex + 1) % _particles.size();

	float randFloat = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
	float randAngle = _info.minSpawnAngle + ((_info.maxSpawnAngle - _info.minSpawnAngle) * randFloat);

	Vector3 rotAxis = (Dot(_info.spawnDirection, Vector3::YAxis) >= 0.99f) ? Vector3::XAxis : Vector3::YAxis;
	rotAxis = Normalize(Cross(rotAxis, _info.spawnDirection));
	Matrix4 matRot = Matrix4::RotationAxis(rotAxis, randAngle);
	Vector3 spawnDir = TransformNormal(_info.spawnDirection, matRot);

	randFloat = static_cast<float>(rand() / static_cast<float>(RAND_MAX));
	float speed = _info.minSpeed + ((_info.maxSpeed - _info.minSpeed) * randFloat);
	p.Activate(_info.particleInfo, _info.spawnPosition, spawnDir * speed);

}

void ParticleSystem::Initialize(const ParticleSystemInfo& info)
{
	_info = info;
	_nextAvailableParticleIndex = 0;
	_nextSpawn = info.spawnDelay;
	_time = info.lifeTime;
	_particles.resize(info.maxParticles);
	for (auto& p : _particles)
	{
		p.Initialize();
	}
}

void ParticleSystem::Terminate()
{
	for (auto& p : _particles)
	{
		p.Terminate();
	}
}

void ParticleSystem::Update(const float deltaTime)
{
	if (_time > 0.f)
	{
		_time -= deltaTime;
		_nextSpawn -= deltaTime;
		if (_nextSpawn <= 0.f)
		{
			SpawnParticles();
		}
		for (auto& p : _particles)
		{
			p.Update(deltaTime);
		}
	}
}

void ParticleSystem::DebugUI()
{
	if (ImGui::CollapsingHeader("Particles"), ImGuiTreeNodeFlags_DefaultOpen)
	{
		ImGui::DragInt("Max Particles", &_info.maxParticles);
		ImGui::DragFloat3("Spawn Position##Part", &_info.spawnPosition.x);
		if (ImGui::DragFloat3("Spawn Direction##Part", &_info.spawnDirection.x))
		{
			_info.spawnDirection = xe::Math::Normalize(_info.spawnDirection);
		}
		ImGui::DragInt("Min Particles per Emit", &_info.minParticlesPerEmit);
		ImGui::DragInt("Max Particles per Emit", &_info.maxParticlesPerEmit);
		ImGui::DragFloat("Min Time Between Particles", &_info.minTimeBetweenParticles);
		ImGui::DragFloat("Max Time Between Particles", &_info.maxTimeBetweenParticles);
		ImGui::DragFloat("Min Spawn Angle", &_info.minSpawnAngle, 0.01f);
		ImGui::DragFloat("Max Spawn Angle", &_info.maxSpawnAngle, 0.01f);
		ImGui::DragFloat("Min Speed##Part", &_info.minSpeed);
		ImGui::DragFloat("Max Speed##Part", &_info.maxSpeed);
		ImGui::DragFloat("Particle Lifetime", &_info.particleInfo.lifetime);
		ImGui::ColorEdit4("Start Color##Part", &_info.particleInfo.colorStart.r);
		ImGui::ColorEdit4("End Color##Part", &_info.particleInfo.colorEnd.r);
		ImGui::DragFloat3("Scale Start##Part", &_info.particleInfo.scaleStart.x);
		ImGui::DragFloat3("Scale End##Part", &_info.particleInfo.scaleEnd.x);
	}
}
