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

		void Initialize(const std::filesystem::path& filepath);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void SetTexture(const Texture* texture, uint32_t slot = 0);
		void DebugUI();

		void SetMode(const Mode mode);

	private:
		struct PostProcData
		{
			Mode mode = Mode::None;
			float param0 = { 0.f };
			float param1 = { 0.f };
			float param2 = { 0.f };
		};

		using PostProcBuffer = TypedContantBuffer<PostProcData>;
		PostProcBuffer m_postProcBuffer;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
		Sampler m_sampler;
		std::array<const Texture*, 4> m_textures;

		Mode m_mode = Mode::None;

		float m_mirrorScaleX = -1.f;
		float m_mirrorScaleY = -1.f;
		Color m_monochromeColor = xe::Colors::White;
		float m_blurAmt = 5.f;
		float m_chromAbAmt = 0.005f;
	};
}

#endif //!__XE_GRAPHICS_POSTPROCEFFECT_H__
