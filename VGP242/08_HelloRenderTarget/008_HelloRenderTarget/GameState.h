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
	xe::Graphics::SimpleEffect _simpleEffect;
	std::list<xe::Graphics::RenderObject> _renderObjects;
	xe::Graphics::RenderTarget _renderTarget;


	xe::Graphics::Camera _rtCamera;
	xe::Graphics::SimpleEffect _rtSimpleEffect;
	int _selectedObj = 0;

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