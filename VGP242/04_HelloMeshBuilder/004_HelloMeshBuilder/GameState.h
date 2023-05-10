#pragma once
#include "XephEngine/include/XephEngine.h"

class GameState : public xe::AppState
{
protected:
	virtual void CreateShape() {};

	xe::Graphics::Camera _camera;
	xe::Graphics::ConstantBuffer _constantBuffer;

	xe::Graphics::MeshBuffer _meshBuffer;
	xe::Graphics::VertexShader _vertexShader;
	xe::Graphics::PixelShader _pixelShader;

	xe::Graphics::Sampler _sampler;
	xe::Graphics::Texture _diffuseTexture;

public:
	virtual ~GameState() {};

	void Initialize() override;
	void Terminate() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
};