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

	ID3D11Buffer* _vertexBuffer = nullptr;
	ID3D11VertexShader*  _vertexShader = nullptr;
	ID3D11InputLayout* _inputLayout = nullptr;
	ID3D11PixelShader* _pixelShader = nullptr;

public:
	virtual ~GameState() {};

	void Initialize() override;
	void Terminate() override;
	void Draw() override;
};