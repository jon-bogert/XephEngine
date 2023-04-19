#include "GameState.h"

using namespace xe;
using namespace xe::Math;
using namespace xe::Graphics;

namespace fs = std::filesystem;

void GameState::Initialize()
{
	//create space in Normalized Device Coord (NDC) space (-1 -> 1 for x, y, z)
	CreateShape();

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	// =============================================================================
	//Create a vertex buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(_vertices.size() * sizeof(Vertex));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = _vertices.data();

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initData, &_vertexBuffer);
	ASSERT(SUCCEEDED(hResult), "Failed to create vertex data");
	// =============================================================================
	//
	// =============================================================================
	//Create a vertex shader

	fs::path shaderFile = L"../../../Assets/Shaders/DoSomething.fx";

	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	hResult = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS", "vs_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hResult), "Failed to compile vertex shader");

	hResult = device->CreateVertexShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&_vertexShader
	);
	ASSERT(SUCCEEDED(hResult), "Failed to create vertex shader");
	// =============================================================================
	//
	// =============================================================================
	//Create a input layer

	std::vector<D3D11_INPUT_ELEMENT_DESC> vertexLayout;
	vertexLayout.push_back({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });
	vertexLayout.push_back({ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT });

	hResult = device->CreateInputLayout(
		vertexLayout.data(),
		(UINT)vertexLayout.size(),
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		&_inputLayout
	);
	ASSERT(SUCCEEDED(hResult), "Failed to create input layout");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
	// =============================================================================
	//
	// =============================================================================
	//Create a pixel shader

	hResult = D3DCompileFromFile(
		shaderFile.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS", "ps_5_0",
		shaderFlags, 0,
		&shaderBlob,
		&errorBlob
	);
	if (errorBlob != nullptr && errorBlob->GetBufferPointer() != nullptr)
	{
		LOG("%s", static_cast<const char*> (errorBlob->GetBufferPointer()));
	}
	ASSERT(SUCCEEDED(hResult), "Failed to compile pixel shader");

	hResult = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&_pixelShader
	);
	ASSERT(SUCCEEDED(hResult), "Failed to create pixel shader");
	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void GameState::Terminate()
{
	_vertices.clear();
	SafeRelease(_pixelShader);
	SafeRelease(_inputLayout);
	SafeRelease(_vertexShader);
	SafeRelease(_vertexBuffer);
}

void GameState::Draw()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();

	context->VSSetShader(_vertexShader, nullptr, 0);
	context->IASetInputLayout(_inputLayout);
	context->PSSetShader(_pixelShader, nullptr, 0);

	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	context->Draw((UINT)_vertices.size(), 0);
}
