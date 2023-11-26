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
	xe::Graphics::DirectionalLight _directionalLight;
	xe::Graphics::StandardEffect _standardEffect;
	xe::Graphics::RenderObject _ground;

	xe::Physics::CollisionShape _groundShape;
	xe::Physics::Rigidbody _groundRigidbody;

	xe::Graphics::RenderObject _cloth;
	xe::Graphics::Mesh _clothMesh;
	xe::Physics::Softbody _clothSoftbody;

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