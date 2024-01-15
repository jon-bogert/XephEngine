#ifndef __XE_GRAPHICS_BLOOMEFFECT_H__
#define __XE_GRAPHICS_BLOOMEFFECT_H__

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Sampler.h"
#include "RenderTarget.h"
#include "VertexShader.h"

namespace xe::Graphics
{
	class RenderObject;
	class Texture;

	class BloomEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void DebugUI();

		void SetSourceTexture(const Texture& texture) { m_sourceTexture = &texture; }
		const Texture& GetHorizontalBlurTexture() const { return m_horizontalBlurRenderTarget; }
		const Texture& GetVerticalBlurTexture() const { return m_verticalBlurRenderTarget; }
		const Texture& GetResultTexture() const { return m_verticalBlurRenderTarget; }

		uint32_t GetBlurIterations() { return m_blurIterations; }
		float GetBlurSaturation() { return m_blurSaturation; }

		void SetBlurIterations(uint32_t blurIter) { m_blurIterations = blurIter; }
		void SetBlurSaturation(float blurSat) { m_blurSaturation = blurSat; }

	private:
		struct SettingsData
		{
			float width;
			float height;
			float multiplier;
			uint32_t padding = 0;
		};

		using SettingsBuffer = TypedContantBuffer<SettingsData>;
		SettingsBuffer m_settingsBuffer;

		RenderTarget m_horizontalBlurRenderTarget;
		RenderTarget m_verticalBlurRenderTarget;

		VertexShader m_vertexShader;
		PixelShader m_horizontalPixelShader;
		PixelShader m_verticalPixelShader;

		Sampler m_sampler;

		const Texture* m_sourceTexture = nullptr;

		uint32_t m_blurIterations = 1;
		float m_blurSaturation = 1.f;

	};
}

#endif // !__XE_GRAPHICS_BLOOMEFFECT_H__
