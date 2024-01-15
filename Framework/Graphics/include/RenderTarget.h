#ifndef __XE_GRAPHICS_RENDERTARGET_H__
#define __XE_GRAPHICS_RENDERTARGET_H__

#include "Colors.h"
#include "Texture.h"

namespace xe::Graphics
{
	class RenderTarget final : public Texture
	{
	public:
		RenderTarget() = default;
		~RenderTarget() override;

		void Initialize(const std::filesystem::path& path) override;
		void Initialize(uint32_t width, uint32_t height, Format format) override;
		void Terminate() override;

		void BeginDraw(Color clearColor = Colors::Black);
		void EndDraw();

	private:
		//CURRENT
		ID3D11RenderTargetView* m_renderTargetView = nullptr;
		ID3D11DepthStencilView* m_depthStencilView = nullptr;
		D3D11_VIEWPORT m_viewport{};

		//OLD
		ID3D11RenderTargetView* m_oldRenderTargetView = nullptr;
		ID3D11DepthStencilView* m_oldDepthStencilView = nullptr;
		D3D11_VIEWPORT m_oldViewport{};
	};
}

#endif //!__XE_GRAPHICS_RENDERTARGET_H__