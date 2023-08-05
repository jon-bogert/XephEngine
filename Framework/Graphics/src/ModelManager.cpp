#include "Pch.h"
#include "ModelManager.h"

#include "ModelIO.h"

namespace
{
	std::unique_ptr<xe::Graphics::ModelManager> _modelManager;
}

void xe::Graphics::ModelManager::Initialize()
{
	ASSERT(_modelManager == nullptr, "ModelManager -> is already initialized");
	_modelManager = std::make_unique<ModelManager>();
}

void xe::Graphics::ModelManager::Terminate()
{
	_modelManager.reset();
}

xe::Graphics::ModelID xe::Graphics::ModelManager::GetModelID(const std::filesystem::path& filepath)
{
	return std::filesystem::hash_value(filepath);
}

xe::Graphics::ModelID xe::Graphics::ModelManager::LoadModel(const std::filesystem::path& filepath)
{
	const ModelID modelID = GetModelID(filepath);
	auto [iter, success] = _modelManager->_inventory.insert({ modelID, nullptr });
	if (success)
	{
		std::unique_ptr<Model>& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(filepath, *modelPtr);
		ModelIO::LoadMaterial(filepath, *modelPtr);
	}
	return modelID;
}

xe::Graphics::Model* xe::Graphics::ModelManager::GetModel(ModelID id)
{
	auto model = _modelManager->_inventory.find(id);
	if (model != _modelManager->_inventory.end())
	{
		return model->second.get();
	}
	return nullptr;
}
