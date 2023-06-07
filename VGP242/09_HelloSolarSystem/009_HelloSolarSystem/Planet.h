#pragma once
#include "XephEngine/include/XephEngine.h"

class Planet
{
	xe::Graphics::RenderObject* _renderObject = nullptr;
	float _orbitRad = 0.f;
	float _orbitSpeed = 0.1f;
	float _currOrbitRot = 0.f;

	bool _showOrbit = true;

public:

	enum class Size { XL, L, M, S };

	void Init(Size size, std::wstring textureName, float orbitRad, std::list<xe::Graphics::RenderObject>& renderObjects);
	void Update(const float& deltaTime);

	static void SetSphereOptions(uint32_t slices, uint32_t rings);

	bool GetShowOrbit() const;
	void SetShowOrbit(const bool setTo);
};