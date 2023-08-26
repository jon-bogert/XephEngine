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
	xe::Graphics::ShadowEffect _shadowEffect;
	xe::Graphics::PostProcEffect _postProcEffect;
	xe::Graphics::BloomEffect _bloomEffect;
	xe::Graphics::RenderObject _sun;
	xe::Graphics::RenderObject _earth;
	xe::Graphics::RenderObject _screenQuad;
	xe::Graphics::RenderTarget _baseRenderTarget;
	xe::Graphics::RenderTarget _bloomRenderTarget;
	xe::Graphics::Texture _combineTexture;




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