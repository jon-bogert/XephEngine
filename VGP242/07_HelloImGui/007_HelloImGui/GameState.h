#pragma once
#include "XephEngine/include/XephEngine.h"

enum class ShapeType
{
	Transform,
	Sphere,
	BoxWireframe,
	BoxFilled,
	Custom,
	Count
};

class GameState : public xe::AppState
{
protected:
	xe::Graphics::Camera _camera;
	ShapeType _shapeType = ShapeType::Transform;
	float _sphereRadius = 1.f;
	Color _shapeColor = Colors::Red;
	bool _useTransp = false;
	xe::Math::Vector3 _transfPosition = { 0.f, 0.f, 0.f };

public:
	

	virtual ~GameState() {};

	void Initialize() override;
	void Terminate() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
	void DebugUI() override;

protected:
	void UpdateCameraControl(const float& deltaTime);
};