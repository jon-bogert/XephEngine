#ifndef XE_GRAPHICS_VERTEXSHADER_H
#define XE_GRAPHICS_VERTEXSHADER_H

namespace xe::Graphics
{
	class VertexShader final
	{
		ID3D11VertexShader* _vertexShader = nullptr;
		ID3D11InputLayout* _inputLayout = nullptr;

	public:
		template<class VertexType>
		void Initialize(const std::filesystem::path& filePath)
		{
			Initialize(filePath, VertexType::Format);
		}
		void Initialize(const std::filesystem::path& filePath, uint32_t format);
		void Terminate();
		void Bind();
	};
}

#endif