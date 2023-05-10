#include "Pch.h"
#include "MeshBuffer.h"
#include "GraphicsSystem.h"

void xe::Graphics::MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount)
{
	CreateVertexBuffer(vertices, vertexSize, vertexCount);
}

void xe::Graphics::MeshBuffer::Initialize(const void* vertices, uint32_t vertexSize, uint32_t vertexCount, const uint32_t* indices, uint32_t indexCount)
{
	CreateVertexBuffer(vertices, vertexSize, vertexCount);
	CreateIndexBuffer(indices, indexCount);
}

void xe::Graphics::MeshBuffer::Terminate()
{
	SafeRelease(_vertexBuffer);
	SafeRelease(_indexBuffer);
}

void xe::Graphics::MeshBuffer::SetTopology(Topology topology)
{
	switch (topology)
	{
	case Topology::Points:
		_topology = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		break;
	case Topology::Lines:
		_topology = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
		break;
	case Topology::Triangles:
		_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		break;
	}
}

void xe::Graphics::MeshBuffer::Draw()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();

	context->IASetPrimitiveTopology(_topology);

	UINT stride = _vertexSize;
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	if (_indexBuffer)
	{
		context->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		context->DrawIndexed(_indexCount, 0, 0);
	}
	else
	{
		context->Draw((UINT)_vertexCount, 0);
	}
}

void xe::Graphics::MeshBuffer::CreateVertexBuffer(const void* vertices, uint32_t vertexSize, uint32_t vertexCount)
{
	_vertexSize = vertexSize;
	_vertexCount = vertexCount;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(_vertexSize * vertexCount);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = vertices;

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initData, &_vertexBuffer);
	ASSERT(SUCCEEDED(hResult), "Failed to create vertex data");
}

void xe::Graphics::MeshBuffer::CreateIndexBuffer(const uint32_t* indices, uint32_t indexCount)
{
	if (indexCount == 0) return;

	_indexCount = indexCount;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(indexCount * sizeof(uint32_t));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = indices;

	HRESULT hResult = device->CreateBuffer(&bufferDesc, &initData, &_indexBuffer);
	ASSERT(SUCCEEDED(hResult), "Failed to create index data");
}
