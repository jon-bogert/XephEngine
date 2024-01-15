#ifndef __XE_GRAPHICS_TEXTUREMANAGER_H__
#define __XE_GRAPHICS_TEXTUREMANAGER_H__

#include "Texture.h"

namespace xe::Graphics
{
	using TextureID = size_t;
	class TextureManager final
	{
	public:
		TextureManager();
		~TextureManager();

		static void Initialize(const std::filesystem::path& root);
		static void Terminate();

		static void SetRootDirectory(const std::filesystem::path& rootDir);

		static TextureID LoadTexture(const std::filesystem::path& filename, bool useRootDir = true);
		static const Texture* GetTexture(TextureID id);
		static void BindVertexShader(TextureID id, uint32_t slot);
		static void BindPixelShader(TextureID id, uint32_t slot);
	private:

		void _Initialize(const std::filesystem::path& root);
		void _SetRootDirectory(const std::filesystem::path& rootDir)const;

		void _SetRootDirectory(const std::filesystem::path& rootDir);

		TextureID _LoadTexture(const std::filesystem::path& filename, bool useRootDir = true);
		const Texture* _GetTexture(TextureID id);
		void _BindVertexShader(TextureID id, uint32_t slot);
		void _BindPixelShader(TextureID id, uint32_t slot);

		static TextureManager& Get();

		TextureManager(const TextureManager&) = delete;
		TextureManager(const TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&&) = delete;

		inline static std::unique_ptr<TextureManager> inst = nullptr;

		using Inventory = std::unordered_map<TextureID, std::unique_ptr<Texture>>;
		Inventory m_inventory;
		std::filesystem::path m_rootDir;
	};
}

#endif //!__XE_GRAPHICS_TEXTUREMANAGER_H__