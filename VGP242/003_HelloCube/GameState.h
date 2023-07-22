#pragma once
#include "XephEngine/include/XephEngine.h"

class GameState : public xe::AppState
{
protected:
	virtual void CreateShape() {};
	struct Vertex
	{
		xe::Math::Vector3 position;
		xe::Color color;
	};

	using Vertices = std::vector<Vertex>;
	Vertices _vertices;

	xe::Graphics::Camera _camera;
	xe::Graphics::ConstantBuffer _constantBuffer;

	xe::Graphics::MeshBuffer _meshBuffer;
	xe::Graphics::VertexShader _vertexShader;
	xe::Graphics::PixelShader _pixelShader;

public:
	virtual ~GameState() {};

	void Initialize() override;
	void Terminate() override;
	void Update(const float& deltaTime) override;
	void Draw() override;
};