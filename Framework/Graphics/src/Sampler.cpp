#include "Pch.h"
#include "Sampler.h"

#include "GraphicsSystem.h"

namespace
{
	using namespace xe::Graphics;
	D3D11_FILTER GetFilter(Sampler::Filter filter)
	{
		switch (filter)
		{
		case Sampler::Filter::Point:
			return D3D11_FILTER_MIN_MAG_MIP_POINT;
		case Sampler::Filter::Linear:
			return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		case Sampler::Filter::Anisotropic:
			return D3D11_FILTER_ANISOTROPIC;
		default:
			ASSERT(false, "FILTER: missing filter mode");
		}
	}

	D3D11_TEXTURE_ADDRESS_MODE GetAddressMode(Sampler::AddressMode addressMode)
	{
		switch (addressMode)
		{
		case Sampler::AddressMode::Border:
			return D3D11_TEXTURE_ADDRESS_BORDER;
		case Sampler::AddressMode::Clamp:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case Sampler::AddressMode::Mirror:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case Sampler::AddressMode::Wrap:
			return D3D11_TEXTURE_ADDRESS_WRAP;
		default:
			ASSERT(false, "TEXTURE ADDRESS: missing Address mode");
		}
	}
}

xe::Graphics::Sampler::~Sampler()
{
	ASSERT(_sampler == nullptr, "Sampler: need to call termainate befire destructor");
}

void xe::Graphics::Sampler::Initialize(Filter filter, AddressMode addressMode)
{
	D3D11_FILTER d3dFilter = GetFilter(filter);
	D3D11_TEXTURE_ADDRESS_MODE d3dAddressMode = GetAddressMode(addressMode);

	D3D11_SAMPLER_DESC desc{};
	desc.Filter = d3dFilter;
	desc.AddressU = d3dAddressMode;
	desc.AddressV = d3dAddressMode;
	desc.AddressW = d3dAddressMode;
	desc.BorderColor[0] = 1.0;
	desc.BorderColor[1] = 1.0;
	desc.BorderColor[2] = 1.0;
	desc.BorderColor[3] = 1.0;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	HRESULT hResult = device->CreateSamplerState(&desc, &_sampler);
	ASSERT(SUCCEEDED(hResult), "Sampler: failed to initialize");
}

void xe::Graphics::Sampler::Terminate()
{
	SafeRelease(_sampler);
}

void xe::Graphics::Sampler::BindVertexShader(uint32_t slot)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->VSSetSamplers(slot, 1, &_sampler);
}

void xe::Graphics::Sampler::BindPixelShader(uint32_t slot)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->PSSetSamplers(slot, 1, &_sampler);
}
