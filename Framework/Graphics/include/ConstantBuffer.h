#ifndef __XE_GRAPHICS_CONSTBUFFER_H__
#define __XE_GRAPHICS_CONSTBUFFER_H__

namespace xe::Graphics
{
	class ConstantBuffer
	{
	public:
		ConstantBuffer() = default;
		virtual ~ConstantBuffer();

		void Initialize(uint32_t bufferSize);
		void Terminate();

		void Update(const void* data) const;

		void BindVertexShader(uint32_t slot);
		void BindPixelShader(uint32_t slot);

	private:
		ID3D11Buffer* m_constantBuffer = nullptr;
	};


	template <class DataType>
	class TypedContantBuffer final : public ConstantBuffer
	{
	public:
		void Initialize()
		{
			static_assert(sizeof(DataType) % 16 == 0, "Data type must be 16 byte alligned"); // Make sure data is aligned in 16-byte for faster GPU Performance;
			ConstantBuffer::Initialize(sizeof(DataType));
		}

		void Update(const DataType& data) const
		{
			ConstantBuffer::Update(&data);
		}
	};
}

#endif // !_XE_GRAPHICS_CONSTBUFFER_H_
