#ifndef XE_GRAPHICS_BLENDSTATE_H
#define XE_GRAPHICS_BLENDSTATE_H

namespace xe::Graphics
{
	class BlendState final
	{
		ID3D11BlendState* _blendState = nullptr;

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
	};
}

#endif

