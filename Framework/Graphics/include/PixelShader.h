#ifndef XE_GRAPHICS_PIXELSHADER_H
#define XE_GRAPHICS_PIXELSHADER_H

namespace xe::Graphics
{
	class PixelShader final
	{
		ID3D11PixelShader* _pixelShader = nullptr;

	public:
		void Initialize(const std::filesystem::path& filePath);
		void Terminate();
		void Bind();
	};
}

#endif
