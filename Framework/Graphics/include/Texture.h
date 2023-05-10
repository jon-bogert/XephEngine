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

		Texture() = default;
		virtual ~Texture();

		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;

		Texture(Texture&&) noexcept;
		Texture& operator=(Texture&&) noexcept;

		virtual void Initialize(const std::filesystem::path&& fileName);
		void Terminate();

		void BindVertexShader(uint32_t slot);
		void BindPixelShader(uint32_t slot);

		void* GetRawData() const { return _shaderResourceView; }
	};
}

#endif // XE_GRAPHICS_TEXTURE_H
