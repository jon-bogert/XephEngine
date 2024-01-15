#ifndef __XE_GRAPHICS_GRAPHICSSYSTEM_H__
#define __XE_GRAPHICS_GRAPHICSSYSTEM_H__
#include "Common.h"
#include "Colors.h"

namespace xe::Graphics
{
	class GraphicsSystem final
	{
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

		Color GetClearColor() const;

		uint32_t GetBackBufferWidth() const;
		uint32_t GetBackBufferHeight() const;

		float GetBackBufferAspectRatio() const;

		ID3D11Device* GetDevice() { return m_d3dDevice; }
		ID3D11DeviceContext* GetContext() { return m_immediateContext; }

	private:
		static LRESULT CALLBACK GraphicsSystemMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

		ID3D11Device* m_d3dDevice;
		ID3D11DeviceContext* m_immediateContext;

		IDXGISwapChain* m_swapChain = nullptr;
		ID3D11RenderTargetView* m_renderTargetView = nullptr;

		ID3D11Texture2D* m_depthStencilBuffer = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;

		DXGI_SWAP_CHAIN_DESC m_swapChainDesc{};
		D3D11_VIEWPORT m_viewport{};

		Color m_clearColor = { 0.1f, 0.1f, 0.1f, 0.1f };
		UINT m_vSync = 1;

		GraphicsSystem(const GraphicsSystem&) = delete;
		GraphicsSystem(const GraphicsSystem&&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&) = delete;
		GraphicsSystem& operator=(const GraphicsSystem&&) = delete;
	};
}
#endif //!__XE_GRAPHICS_GRAPHICSSYSTEM_H__
