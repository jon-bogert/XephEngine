#include "Pch.h"
#include "RenderTarget.h"
#include "GraphicsSystem.h"

xe::Graphics::RenderTarget::~RenderTarget()
{
	ASSERT(_renderTargetView == nullptr && _depthStencilView == nullptr, "RenderTarget need to call terminate");
}

void xe::Graphics::RenderTarget::Initialize(const std::filesystem::path& path)
{
	ASSERT(false, "RenderTarget: cannot call create RenderTarget from file");
}

void xe::Graphics::RenderTarget::Initialize(uint32_t width, uint32_t height, Format format)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = GetDXGIFormat(format);
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	ID3D11Device* device = GraphicsSystem::Get().GetDevice();
	ID3D11Texture2D* texture = nullptr;
	HRESULT hResult = device->CreateTexture2D(&desc, nullptr, &texture);
	ASSERT(SUCCEEDED(hResult), "RenderTarget: failed to create texture");

	hResult = device->CreateShaderResourceView(texture, nullptr, &_shaderResourceView);
	ASSERT(SUCCEEDED(hResult), "RenderTarget: failed to create shader resource view");

	hResult = device->CreateRenderTargetView(texture, nullptr, &_renderTargetView);
	ASSERT(SUCCEEDED(hResult), "RenderTarget: failed to create render target view");

	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hResult = device->CreateTexture2D(&desc, nullptr, &texture);
	ASSERT(SUCCEEDED(hResult), "RenderTarget: failed to create depth stencil texture");

	hResult = device->CreateDepthStencilView(texture, nullptr, &_depthStencilView);
	ASSERT(SUCCEEDED(hResult), "RenderTarget: failed to create depth stencil view");

	SafeRelease(texture);

	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(width);
	_viewport.Height = static_cast<float>(height);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}

void xe::Graphics::RenderTarget::Terminate()
{
	Texture::Terminate();

	SafeRelease(_depthStencilView);
	SafeRelease(_renderTargetView);
}

void xe::Graphics::RenderTarget::BeginDraw(Color clearColor)
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();

	//store the current versions
	UINT numViewports = 1;
	context->OMGetRenderTargets(1, &_oldRenderTargetView, &_oldDepthStencilView);
	context->RSGetViewports(&numViewports, &_oldViewport);

	//apply the render target versions
	context->ClearRenderTargetView(_renderTargetView, &clearColor.r);
	context->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.f, 0.f);
	context->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
	context->RSSetViewports(1, &_viewport);
}

void xe::Graphics::RenderTarget::EndDraw()
{
	ID3D11DeviceContext* context = GraphicsSystem::Get().GetContext();
	context->OMSetRenderTargets(1, &_oldRenderTargetView, _oldDepthStencilView);
	context->RSSetViewports(1, &_oldViewport);
}
