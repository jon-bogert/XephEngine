#ifndef __XE_GRAPHICS_VERTEXSHADER_H__
#define __XE_GRAPHICS_VERTEXSHADER_H__

namespace xe::Graphics
{
	class VertexShader final
	{
	public:
		template<class VertexType>
		void Initialize(const std::filesystem::path& filePath)
		{
			Initialize(filePath, VertexType::Format);
		}
		void Initialize(const std::filesystem::path& filePath, uint32_t format);
		void Terminate();
		void Bind();

	private:
		ID3D11VertexShader* m_vertexShader = nullptr;
		ID3D11InputLayout* m_inputLayout = nullptr;
	};
}

#endif //!__XE_GRAPHICS_VERTEXSHADER_H__