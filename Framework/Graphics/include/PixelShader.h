#ifndef __XE_GRAPHICS_PIXELSHADER_H__
#define __XE_GRAPHICS_PIXELSHADER_H__

namespace xe::Graphics
{
	class PixelShader final
	{
		ID3D11PixelShader* _pixelShader = nullptr;

	public:
		void Initialize(const std::filesystem::path& filePath, const char* entryPoint = "PS");
		void Terminate();
		void Bind();
	};
}

#endif
