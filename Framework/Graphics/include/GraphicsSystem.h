#ifndef XE_GRAPHICS_GRAPHICSSYSTEM_H
#define XE_GRAPHICS_GRAPHICSSYSTEM_H
#include "Common.h"
#include "Colors.h"

namespace xe::Graphics
{
	class GraphicsSystem final
	{
		static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

		ID3D11Device* _d3dDevice;
		ID3D11DeviceContext* _immediateContext;

		IDXGISwapChain* _swapChain = nullptr;
		ID3D11RenderTargetView* _renderTargetView = nullptr;

		ID3D11Texture2D* _depthStencilBuffer = nullptr;
		ID3D11DepthStencilView* _depthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC _swapChainDesc{};
		D3D11_VIEWPORT _viewport{};

		Color _clearColor = {0.1f, 0.1f, 0.1f, 0.1f};
		UINT _vSync = 1;

		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&&) = delete;

	public:
		GraphicsSystem() = default;
		~GraphicsSystem();

		static void Initialize(HWND window, bool isFullscreen);
		static void Terminate();
		static GraphicsSystem& Get();

		void _Initialize(HWND window, bool isFullscreen);
		void _Terminate();

		void BeginRender();
		void EndRender();

		void ToggleFullscreen();
		void Resize(uint32_t width, uint32_t height);

		void ResetRenderTarget();
		void ResetViewport();

		void SetClearColor(const Color& color);
		void SetVSync(bool isOn);

		uint32_t GetBackBufferWidth() const;
		uint32_t GetBackBufferHeight() const;

		float GetBackBufferAspectRatio() const;

		ID3D11Device* GetDevice() { return _d3dDevice; }
		ID3D11DeviceContext* GetContext() { return _immediateContext; }
	};
}
#endif
