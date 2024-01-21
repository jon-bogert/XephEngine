#pragma once

#include "Texture.h"

namespace xe::Graphics
{
	using TextureID = size_t;
	class TextureManager final
	{
		using Inventory = std::unordered_map<TextureID, std::unique_ptr<Texture>>;
		Inventory _inventory;
		std::filesystem::path _rootDir;

		inline static std::unique_ptr<TextureManager> inst = nullptr;

		static TextureManager& Get();

		TextureManager(const TextureManager&) = delete;
		TextureManager(const TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&&) = delete;

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


	};
}