#ifndef __XE_GRAPHICS_CONSTBUFFER_H__
#define __XE_GRAPHICS_CONSTBUFFER_H__

namespace xe::Graphics
{
	class ConstantBuffer
	{
		ID3D11Buffer* _constantBuffer = nullptr;

	public:
		ConstantBuffer() = default;
		virtual ~ConstantBuffer();

		void Initialize(uint32_t bufferSize);
		void Terminate();

		void Update(const void* data);

		void BindVertexShader(uint32_t slot);
		void BindPixelShader(uint32_t slot);
	};
}


#endif // XE_GRAPHICS_CONSTBUFFER_H
