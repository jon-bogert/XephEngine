#include "Planet.h"
#include "Graphics/include/VertexTypes.h"
#include "Graphics/include/MeshTypes.h"

using namespace xe;
using namespace xe::Graphics;

namespace
{
	float GetPlanetRadius(Planet::Size size)
	{
		switch (size)
		{
		case Planet::Size::XL:
			return 2.f;
		case Planet::Size::L:
			return 1.f;
		case Planet::Size::M:
			return .5f;
		case Planet::Size::S:
			return .25f;
		}
	}

	uint32_t slices = 32;
	uint32_t rings = 32;
}


void Planet::Init(Size size, std::wstring textureName, float orbitRad, std::list<RenderObject> &renderObjects)
{
	_orbitRad = orbitRad;

	MeshPX mesh = MeshBuilder::CreateUVSpherePX(slices, rings, GetPlanetRadius(size));
	_renderObject = &renderObjects.emplace_back();
	_renderObject->meshBuffer.Initialize(mesh);
	_renderObject->diffuseTexture.Initialize(L"../../../Assets/Textures/planets/" + textureName + L".jpg");
	_renderObject->transform.position.x = orbitRad;
}

void Planet::Update(const float& deltaTime)
{
	//return if the centered (the sun)
	if (_orbitRad == 0.f)
		return;

	// update orbit angle
	_currOrbitRot += _orbitSpeed * deltaTime;

	// check and reset rotation if over full cycle
	while (_currOrbitRot >= xe::Math::Const::TwoPi)
		_currOrbitRot -= xe::Math::Const::TwoPi;

	//update position based on orbit angle;
	_renderObject->transform.position.x = std::cos(_currOrbitRot) * _orbitRad;
	_renderObject->transform.position.z = std::sin(_currOrbitRot) * _orbitRad;

#ifdef _DEBUG
	if (_showOrbit)
		SimpleDraw::AddGroundCircle(32, _orbitRad, Colors::White);
#endif // _DEBUG
}

void Planet::SetSphereOptions(uint32_t slices_, uint32_t rings_)
{
	slices = slices_;
	rings = rings_;
}

bool Planet::GetShowOrbit() const
{
	return _showOrbit;
}

void Planet::SetShowOrbit(const bool setTo)
{
	_showOrbit = setTo;
}
