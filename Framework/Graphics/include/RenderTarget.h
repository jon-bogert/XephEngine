#ifndef XE_GRAPHICS_RENDERTARGET_H
#define XE_GRAPHICS_RENDERTARGET_H

#include "Colors.h"
#include "Texture.h"

namespace xe::Graphics
{
	class RenderTarget final : public Texture
	{
		//CURRENT
		ID3D11RenderTargetView* _renderTargetView = nullptr;
		ID3D11DepthStencilView* _depthStencilView = nullptr;
		D3D11_VIEWPORT _viewport{};

		//OLD
		ID3D11RenderTargetView* _oldRenderTargetView = nullptr;
		ID3D11DepthStencilView* _oldDepthStencilView = nullptr;
		D3D11_VIEWPORT _oldViewport{};

	public:
		RenderTarget() = default;
		~RenderTarget() override;

		void Initialize(const std::filesystem::path& path) override;
		void Initialize(uint32_t width, uint32_t height, Format format) override;
		void Terminate() override;

		void BeginDraw(Color clearColor = Colors::Black);
		void EndDraw();
	};
}

#endif // XE_GRAPHICS_RENDERTARGET_H