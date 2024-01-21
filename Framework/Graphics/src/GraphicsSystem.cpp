#include "Pch.h"
#include "GraphicsSystem.h"

using namespace xe;
using namespace xe::Graphics;

namespace
{
	std::unique_ptr<GraphicsSystem> graphicsSystem;
	Core::WindowMessageHandler windowMessageHandler;
}

LRESULT xe::Graphics::GraphicsSystem::GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (graphicsSystem)
	{
		switch (message)
		{
		case WM_SIZE:
			const uint32_t width = static_cast<uint32_t>(LOWORD(lParam));
			const uint32_t height = static_cast<uint32_t>(HIWORD(lParam));
			graphicsSystem->Resize(width, height);
			break;
		}
	}
	return windowMessageHandler.ForwardMessage(handle, message, wParam, lParam);
}

xe::Graphics::GraphicsSystem::~GraphicsSystem()
{
	ASSERT(_d3dDevice == nullptr, "GraphicsSystem must be terminated before cleanup");
}

void xe::Graphics::GraphicsSystem::Initialize(HWND window, bool isFullscreen)
{
	ASSERT(graphicsSystem == nullptr, "GraphicsSystem is already initialized");
	graphicsSystem = std::make_unique<GraphicsSystem>();
	graphicsSystem->_Initialize(window, isFullscreen);
}

void xe::Graphics::GraphicsSystem::Terminate()
{
	if (graphicsSystem != nullptr)
	{
		graphicsSystem->_Terminate();
		graphicsSystem.reset();
	}
}

GraphicsSystem& xe::Graphics::GraphicsSystem::Get()
{
	ASSERT(graphicsSystem != nullptr, "GraphicsSystem is not created");
	return *(graphicsSystem.get());
}

void xe::Graphics::GraphicsSystem::_Initialize(HWND window, bool isFullscreen)
{
	RECT clientRect{};
	GetClientRect(window, &clientRect);
	UINT width = (UINT)(clientRect.right - clientRect.left);
	UINT height = (UINT)(clientRect.bottom - clientRect.top);

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = window;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = !isFullscreen;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	HRESULT hResult = D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&_swapChain,
		&_d3dDevice,
		nullptr,
		&_immediateContext
	);

	ASSERT(SUCCEEDED(hResult), "GraphicsSystem failt to initialize device or swap chain");
	_swapChain->GetDesc(&_swapChainDesc);

	Resize(GetBackBufferWidth(), GetBackBufferHeight());
	windowMessageHandler.Hook(window, GraphicsSystemMessageHandler);
}

void xe::Graphics::GraphicsSystem::_Terminate()
{
	windowMessageHandler.UnHook();

	SafeRelease(_depthStencilView);
	SafeRelease(_depthStencilBuffer);
	SafeRelease(_renderTargetView);
	SafeRelease(_swapChain);
	SafeRelease(_immediateContext);
	SafeRelease(_d3dDevice);
}

void xe::Graphics::GraphicsSystem::ToggleFullscreen()
{
	BOOL fullscreen;
	_swapChain->GetFullscreenState(&fullscreen, nullptr);
	_swapChain->SetFullscreenState(!fullscreen, nullptr);
}

void xe::Graphics::GraphicsSystem::Resize(uint32_t width, uint32_t height)
{
	_immediateContext->OMSetRenderTargets(0, nullptr, nullptr);

	SafeRelease(_renderTargetView);
	SafeRelease(_depthStencilView);

	HRESULT hResult;
	if (width != GetBackBufferWidth() || height != GetBackBufferHeight())
	{
		hResult = _swapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
		ASSERT(SUCCEEDED(hResult), "GraphicsSystem failed to access the swap chain view");

		_swapChain->GetDesc(&_swapChainDesc);
	}

	ID3D11Texture2D* backBuffer = nullptr;
	hResult = _swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	ASSERT(SUCCEEDED(hResult), "GraphicsSystem failed to get back buffer");

	hResult = _d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &_renderTargetView);
	SafeRelease(backBuffer);
	ASSERT(SUCCEEDED(hResult), "GraphicsSystem failt to create render target");

	D3D11_TEXTURE2D_DESC descDepth{};
	descDepth.Width = GetBackBufferWidth();
	descDepth.Height = GetBackBufferHeight();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hResult = _d3dDevice->CreateTexture2D(&descDepth, nullptr, &_depthStencilBuffer);
	ASSERT(SUCCEEDED(hResult), "GraphicsSystem failed to create stencil buffer");

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV{};
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hResult = _d3dDevice->CreateDepthStencilView(_depthStencilBuffer, &descDSV, &_depthStencilView);
	ASSERT(SUCCEEDED(hResult), "GraphicsSystem failed to create depth stencil view");

	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
	_viewport.Width = static_cast<float>(GetBackBufferWidth());
	_viewport.Height = static_cast<float>(GetBackBufferHeight());
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
	_viewport.TopLeftX = 0;
	_viewport.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &_viewport);
}

void xe::Graphics::GraphicsSystem::BeginRender()
{
	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
	_immediateContext->ClearRenderTargetView(_renderTargetView, (FLOAT*)(&_clearColor));
	_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0.f);
}

void xe::Graphics::GraphicsSystem::EndRender()
{
	_swapChain->Present(_vSync, 0);
}

void xe::Graphics::GraphicsSystem::ResetRenderTarget()
{
	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);
}

void xe::Graphics::GraphicsSystem::ResetViewport()
{
	_immediateContext->RSSetViewports(1, &_viewport);
}

void xe::Graphics::GraphicsSystem::SetClearColor(const Color& color)
{
	_clearColor = color;
}

void xe::Graphics::GraphicsSystem::SetVSync(bool isOn)
{
	_vSync = (isOn) ? 1: 0;
}

Color xe::Graphics::GraphicsSystem::GetClearColor() const
{
	return _clearColor;
}

uint32_t xe::Graphics::GraphicsSystem::GetBackBufferWidth() const
{
	return _swapChainDesc.BufferDesc.Width;
}

uint32_t xe::Graphics::GraphicsSystem::GetBackBufferHeight() const
{
	return _swapChainDesc.BufferDesc.Height;
}

float xe::Graphics::GraphicsSystem::GetBackBufferAspectRatio() const
{
	return static_cast<float>(GetBackBufferWidth()) / static_cast<float>(GetBackBufferHeight());
}
