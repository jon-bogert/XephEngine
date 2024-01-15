#ifndef __XE_GRAPHICS_BLENDSTATE_H__
#define __XE_GRAPHICS_BLENDSTATE_H__

namespace xe::Graphics
{
	class BlendState final
	{
	public:
		static void Clear();
		enum class Mode { Opaque, AlphaBlend, AlphaPremultiplied, Additive };

		BlendState() = default;
		~BlendState();

		BlendState(const BlendState&) = delete;
		BlendState& operator=(const BlendState&) = delete;

		void Initialize(Mode mode);
		void Terminate();

		void Set();

	private:
		ID3D11BlendState* m_blendState = nullptr;
	};
}

#endif //!__XE_GRAPHICS_BLENDSTATE_H__

