#ifndef __XE_GRAPHICS_POSTPROCEFFECT_H__
#define __XE_GRAPHICS_POSTPROCEFFECT_H__

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Sampler.h"
#include "Colors.h"

namespace xe::Graphics
{
	class RenderObject;
	class Texture;

	class PostProcEffect
	{
	public:
		enum class Mode
		{
			None,
			Monochrome,
			Invert,
			Mirror,
			Blur,
			Combine2,
			MotionBlur,
			ChromAberr,
			Count
		};

	private:
		struct PPData
		{
			Mode mode = Mode::None;
			float param0 = { 0.f };
			float param1 = { 0.f };
			float param2 = { 0.f };
		};

		using PostProcBuffer = TypedContantBuffer<PPData>;
		PostProcBuffer _postProcBuffer;

		VertexShader _vertexShader;
		PixelShader _pixelShader;
		Sampler _sampler;
		std::array<const Texture*, 4> _textures;

		Mode _mode = Mode::None;

		float _mirrorScaleX = -1.f;
		float _mirrorScaleY = -1.f;
		Color _monochromeColor = xe::Colors::White;
		float _blurAmt = 5.f;
		float _chromAbAmt = 0.005f;

	public:
		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void SetTexture(const Texture* texture, uint32_t slot = 0);
		void DebugUI();

		void SetMode(const Mode mode);
	};
}

#endif // __XE_GRAPHICS_POSTPROCEFFECT_H__
