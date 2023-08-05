#ifndef __XE_GRAPHICS_MODELMANAGER_H__
#define __XE_GRAPHICS_MODELMANAGER_H__

#include "Model.h"

namespace xe::Graphics
{
	using ModelID = std::size_t;

	class ModelManager final
	{
		static ModelManager& Get();

		using ModelCache = std::map<ModelID, std::unique_ptr<Model>>;
		ModelCache _inventory;

	public:

		ModelManager() = default;
		~ModelManager() = default;

		static void Initialize();
		static void Terminate();

		ModelManager(const ModelManager&) = delete;
		ModelManager(const ModelManager&&) = delete;

		ModelManager& operator=(const ModelManager&) = delete;
		ModelManager& operator=(const ModelManager&&) = delete;

		static ModelID GetModelID(const std::filesystem::path& filepath);
		static ModelID LoadModel(const std::filesystem::path& filepath);

		static Model* GetModel(ModelID id);

	};
}

#endif // __XE_GRAPHICS_MODELMANAGER_H__