#ifndef XE_GRAPHICS_TEXTURE_H
#define XE_GRAPHICS_TEXTURE_H
namespace xe::Graphics
{
	class Texture
	{
	protected:
		ID3D11ShaderResourceView* _shaderResourceView = nullptr;

	public:
		static void UnbindPixelShader(uint32_t slot);

		enum class Format
		{
			RGBA_U8,
			RGBA_U32
		};

		Texture() = default;
		virtual ~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;

		virtual void Initialize(const std::filesystem::path& fileName);
		virtual void Initialize(uint32_t width, uint32_t height, Format format);
		virtual void Terminate();

		void BindVertexShader(uint32_t slot) const;
		void BindPixelShader(uint32_t slot) const;

		void* GetRawData() const { return _shaderResourceView; }

	protected:
		DXGI_FORMAT GetDXGIFormat(Format format);
	};
}

#endif // XE_GRAPHICS_TEXTURE_H
