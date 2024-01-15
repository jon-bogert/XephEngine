#ifndef __XE_GRAPHICS_PIXELSHADER_H__
#define __XE_GRAPHICS_PIXELSHADER_H__

namespace xe::Graphics
{
	class PixelShader final
	{
	public:
		void Initialize(const std::filesystem::path& filePath, const char* entryPoint = "PS");
		void Terminate();
		void Bind();

	private:
		ID3D11PixelShader* m_pixelShader = nullptr;
	};
}

#endif //!__XE_GRAPHICS_PIXELSHADER_H__
