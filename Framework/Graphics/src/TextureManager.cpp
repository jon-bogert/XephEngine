#include "Pch.h"
#include "TextureManager.h"

xe::Graphics::TextureManager& xe::Graphics::TextureManager::Get()
{
	ASSERT(inst.get(), "TextureManager -> has not been initialized");
	return *inst;
}

xe::Graphics::TextureManager::TextureManager()
{
}

xe::Graphics::TextureManager::~TextureManager()
{
	for (auto& [id, texture] : _inventory)
	{
		texture->Terminate();
	}

	_inventory.clear();
}

void xe::Graphics::TextureManager::Initialize(const std::filesystem::path& root)
{
	ASSERT(!inst.get(), "Cannot initialize TextureManager more than once");
	inst = std::make_unique<TextureManager>();
	inst->_rootDir = root;
}

void xe::Graphics::TextureManager::Terminate()
{
	inst.reset();
}

void xe::Graphics::TextureManager::SetRootDirectory(const std::filesystem::path& rootDir)
{
	inst->_SetRootDirectory(rootDir);
}

xe::Graphics::TextureID xe::Graphics::TextureManager::LoadTexture(const std::filesystem::path& filename, bool useRootDir)
{
	return inst->_LoadTexture(filename, useRootDir);
}

const xe::Graphics::Texture* xe::Graphics::TextureManager::GetTexture(TextureID id)
{
	return inst->_GetTexture(id);
}

void xe::Graphics::TextureManager::BindVertexShader(TextureID id, uint32_t slot)
{
	inst->_BindVertexShader(id, slot);
}

void xe::Graphics::TextureManager::BindPixelShader(TextureID id, uint32_t slot)
{
	inst->_BindPixelShader(id, slot);
}

void xe::Graphics::TextureManager::_SetRootDirectory(const std::filesystem::path& rootDir)
{
	_rootDir = rootDir;
}

xe::Graphics::TextureID xe::Graphics::TextureManager::_LoadTexture(const std::filesystem::path& filename, bool useRootDir)
{
	auto textureID = std::filesystem::hash_value(filename);
	auto [iter, success] = _inventory.insert({ textureID, nullptr });
	if (success)
	{
		auto& texturePtr = iter->second;
		texturePtr = std::make_unique<Texture>();
		texturePtr->Initialize((useRootDir) ? _rootDir / filename : filename);
	}
	return textureID;
}

const xe::Graphics::Texture* xe::Graphics::TextureManager::_GetTexture(TextureID id)
{
	auto iter = _inventory.find(id);
	if (iter != _inventory.end())
	{
		return iter->second.get();
	}
	return nullptr;
}

void xe::Graphics::TextureManager::_BindVertexShader(TextureID id, uint32_t slot)
{
	if (id == 0)
		return;

	auto iter = _inventory.find(id);
	if (iter != _inventory.end())
	{
		iter->second->BindVertexShader(slot);
	}
}

void xe::Graphics::TextureManager::_BindPixelShader(TextureID id, uint32_t slot)
{
	if (id == 0)
		return;

	auto iter = _inventory.find(id);
	if (iter != _inventory.end())
	{
		iter->second->BindPixelShader(slot);
	}
}
