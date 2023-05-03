#include "Pch.h"
#include "ConstantBuffer.h"
#include "GraphicsSystem.h"

using namespace xe::Graphics;

xe::Graphics::ConstantBuffer::~ConstantBuffer()
{
	ASSERT(_constantBuffer == nullptr, "ConstantBuffer not release");
}

void xe::Graphics::ConstantBuffer::Initialize(uint32_t bufferSize)
{
	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = bufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	HRESULT hResult = device->CreateBuffer(&desc, nullptr, &_constantBuffer);
	ASSERT(SUCCEEDED(hResult), "ConstantBuffer failed to create constant buffer");
}

void xe::Graphics::ConstantBuffer::Terminate()
{
	SafeRelease(_constantBuffer);
}

void xe::Graphics::ConstantBuffer::Update(const void* data)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->UpdateSubresource(_constantBuffer, 0, nullptr, data, 0, 0);
}

void xe::Graphics::ConstantBuffer::BindVertexShader(uint32_t slot)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->VSSetConstantBuffers(slot, 1, &_constantBuffer);
}

void xe::Graphics::ConstantBuffer::BindPixelShader(uint32_t slot)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->PSSetConstantBuffers(slot, 1, &_constantBuffer);
}
