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
	xe::Graphics::Animator _characterAnimator;
	xe::Graphics::RenderGroup _character;
	xe::Graphics::ModelID _characterID;
	xe::Graphics::StandardEffect _standardEffect;
	xe::Graphics::RenderObject _ground;
	
	int _animIndex = 0;
	bool _loopAnimation = true;
	bool _drawSkeleton = false;
	float _fps = 0.f;

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