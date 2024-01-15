#ifndef __XE_GRAPHICS_SAMPLER_H__
#define __XE_GRAPHICS_SAMPLER_H__

namespace xe::Graphics
{
	class Sampler final
	{
	public:
		enum class Filter { Point, Linear, Anisotropic };
		enum class AddressMode { Border, Clamp, Mirror, Wrap };

		Sampler() = default;
		~Sampler();

		Sampler(const Sampler&) = delete;
		Sampler(const Sampler&&) = delete;
		Sampler& operator=(Sampler&) = delete;
		Sampler& operator=(Sampler&&) = delete;

		void Initialize(Filter filter, AddressMode addressMode);
		void Terminate();

		void BindVertexShader(uint32_t slot);
		void BindPixelShader(uint32_t slot);

	private:
		ID3D11SamplerState* m_sampler = nullptr;
	};
}

#endif //!__XE_GRAPHICS_SAMPLER_H__
