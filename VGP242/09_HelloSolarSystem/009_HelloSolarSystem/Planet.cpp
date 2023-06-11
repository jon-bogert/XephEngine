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

	using namespace xe::Math;
	void RotateQuaternion(Quaternion& q, float amt, Vector3 axis) {
		// Convert the Euler axis to a unit vector
		axis = Normalize(axis);

		// Convert the Euler angle to a quaternion
		double halfAngle = amt * 0.5;
		double sinHalfAngle = std::sin(halfAngle);
		double cosHalfAngle = std::cos(halfAngle);

		Quaternion rotationQuaternion;
		rotationQuaternion.w = cosHalfAngle;
		rotationQuaternion.x = axis.x * sinHalfAngle;
		rotationQuaternion.y = axis.y * sinHalfAngle;
		rotationQuaternion.z = axis.z * sinHalfAngle;

		// Multiply the rotation quaternion with the original quaternion
		Quaternion rotatedQuaternion;
		rotatedQuaternion.w = rotationQuaternion.w * q.w - rotationQuaternion.x * q.x - rotationQuaternion.y * q.y - rotationQuaternion.z * q.z;
		rotatedQuaternion.x = rotationQuaternion.w * q.x + rotationQuaternion.x * q.w + rotationQuaternion.y * q.z - rotationQuaternion.z * q.y;
		rotatedQuaternion.y = rotationQuaternion.w * q.y - rotationQuaternion.x * q.z + rotationQuaternion.y * q.w + rotationQuaternion.z * q.x;
		rotatedQuaternion.z = rotationQuaternion.w * q.z + rotationQuaternion.x * q.y - rotationQuaternion.y * q.x + rotationQuaternion.z * q.w;

		q = rotatedQuaternion;
	}
}


void Planet::Init(Size size, std::wstring planetName, float orbitRad, std::list<RenderObject> &renderObjects)
{
	_planetName = planetName;
	_orbitRad = orbitRad;

	MeshPX mesh = MeshBuilder::CreateUVSpherePX(slices, rings, GetPlanetRadius(size));
	_renderObject = &renderObjects.emplace_back();
	_renderObject->meshBuffer.Initialize(mesh);
	_renderObject->diffuseTexture.Initialize(L"../../../Assets/Textures/planets/" + planetName + L".jpg");
	_renderObject->transform.position.x = orbitRad;
}

void Planet::Update(const float& deltaTime)
{
	//return if the centered (the sun)
	if (_orbitRad == 0.f)
		return;

	// update orbit angle
	_currOrbitRot += _orbitSpeed * deltaTime;
	_dayRot += _dayRotSpeed * deltaTime;

	// check and reset rotation if over full cycle
	while (_currOrbitRot >= xe::Math::Const::TwoPi)
		_currOrbitRot -= xe::Math::Const::TwoPi;
	while (_dayRot >= xe::Math::Const::TwoPi)
		_dayRot -= xe::Math::Const::TwoPi;

	//update position based on orbit angle;
	_renderObject->transform.position.x = std::cos(_currOrbitRot) * _orbitRad;
	_renderObject->transform.position.z = std::sin(_currOrbitRot) * _orbitRad;
	RotateQuaternion(_renderObject->transform.rotation, _dayRotSpeed * deltaTime, xe::Math::Vector3::YAxis);

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

float Planet::GetOrbitSpeed() const
{
	return _orbitSpeed;
}

void Planet::SetOrbitSpeed(const float orbitSpeed)
{
	_orbitSpeed = orbitSpeed;
}

float Planet::GetDayRotSpeed() const
{
	return _dayRotSpeed;
}

void Planet::SetDayRotSpeed(const float dayRotSpeed)
{
	_dayRotSpeed = dayRotSpeed;
}

std::string Planet::GetPlanetName() const
{
	std::string name;
	for (const wchar_t& c : _planetName)
	{
		name.push_back(static_cast<char>(c));
	}
	return name;
}
