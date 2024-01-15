#include "Pch.h"
#include "BlendState.h"

#include "GraphicsSystem.h"

namespace
{
	using namespace xe::Graphics;
	D3D11_BLEND GetSrcBlend(BlendState::Mode mode)
	{
		switch (mode)
		{
		case BlendState::Mode::Additive:			return D3D11_BLEND_SRC_ALPHA;
		case BlendState::Mode::AlphaBlend:			return D3D11_BLEND_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:	return D3D11_BLEND_ONE;
		case BlendState::Mode::Opaque:				return D3D11_BLEND_ONE;
		default:
			break;
		}
		return D3D11_BLEND_ONE;
	}
	D3D11_BLEND GetDestBlend(BlendState::Mode mode)
	{
		switch (mode)
		{
		case BlendState::Mode::Additive:			return D3D11_BLEND_ONE;
		case BlendState::Mode::AlphaBlend:			return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::AlphaPremultiplied:	return D3D11_BLEND_INV_SRC_ALPHA;
		case BlendState::Mode::Opaque:				return D3D11_BLEND_ZERO;
		default:
			break;
		}
		return D3D11_BLEND_ZERO;
	}
}

void xe::Graphics::BlendState::Clear()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->OMSetBlendState(nullptr, nullptr, UINT_MAX);
}

xe::Graphics::BlendState::~BlendState()
{
	ASSERT(m_blendState == nullptr, "BLendState: need to call terinate");
}

void xe::Graphics::BlendState::Initialize(Mode mode)
{
	D3D11_BLEND srcBlend = GetSrcBlend(mode);
	D3D11_BLEND destBlend = GetDestBlend(mode);

	D3D11_BLEND_DESC desc{};
	desc.RenderTarget[0].BlendEnable = (srcBlend != D3D11_BLEND_ONE) || (destBlend != D3D11_BLEND_ZERO);
	desc.RenderTarget[0].SrcBlend = desc.RenderTarget[0].SrcBlendAlpha = srcBlend;
	desc.RenderTarget[0].DestBlend = desc.RenderTarget[0].DestBlendAlpha = destBlend;
	desc.RenderTarget[0].BlendOp = desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	HRESULT hResult = device->CreateBlendState(&desc, &m_blendState);
	ASSERT(SUCCEEDED(hResult), "BlendState: failed to create blend state");
}

void xe::Graphics::BlendState::Terminate()
{
	SafeRelease(m_blendState);
}

void xe::Graphics::BlendState::Set()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->OMSetBlendState(m_blendState, nullptr, UINT_MAX);
}
