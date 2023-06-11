#pragma once
#include "XephEngine/include/XephEngine.h"

class Planet
{
	xe::Graphics::RenderObject* _renderObject = nullptr;
	std::wstring _planetName;

	float _orbitRad = 0.f;
	float _orbitSpeed = 0.1f;
	float _currOrbitRot = 0.f;

	float _dayRot = 0.f;
	float _dayRotSpeed = 0.1;

	bool _showOrbit = true;

public:

	enum class Size { XL, L, M, S };

	void Init(Size size, std::wstring planetName, float orbitRad, std::list<xe::Graphics::RenderObject>& renderObjects);
	void Update(const float& deltaTime);

	static void SetSphereOptions(uint32_t slices, uint32_t rings);

	bool GetShowOrbit() const;
	void SetShowOrbit(const bool setTo);

	float GetOrbitSpeed() const;
	void SetOrbitSpeed(const float orbitSpeed);

	float GetDayRotSpeed() const;
	void SetDayRotSpeed(const float dayRotSpeed);

	std::string GetPlanetName() const;
};