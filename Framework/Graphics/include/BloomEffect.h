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
		struct SettingsData
		{
			float width;
			float height;
			float multiplier;
			uint32_t padding = 0;
		};

		using SettingsBuffer = TypedContantBuffer<SettingsData>;
		SettingsBuffer _settingsBuffer;

		RenderTarget _horizontalBlurRenderTarget;
		RenderTarget _verticalBlurRenderTarget;

		VertexShader _vertexShader;
		PixelShader _horizontalPixelShader;
		PixelShader _verticalPixelShader;

		Sampler _sampler;

		const Texture* _sourceTexture = nullptr;

		uint32_t _blurIterations = 1;
		float _blurSaturation = 1.f;

	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void DebugUI();

		void SetSourceTexture(const Texture& texture) { _sourceTexture = &texture; }
		const Texture& GetHorizontalBlurTexture() const { return _horizontalBlurRenderTarget; }
		const Texture& GetVerticalBlurTexture() const { return _verticalBlurRenderTarget; }
		const Texture& GetResultTexture() const { return _verticalBlurRenderTarget; }

		uint32_t GetBlurIterations() { return _blurIterations; }
		float GetBlurSaturation() { return _blurSaturation; }

		void SetBlurIterations(uint32_t blurIter) { _blurIterations = blurIter; }
		void SetBlurSaturation(float blurSat) { _blurSaturation = blurSat; }

	};
}

#endif // __XE_GRAPHICS_BLOOMEFFECT_H__
