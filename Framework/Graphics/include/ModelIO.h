#ifndef __XE_GRAPHICS_MODELIO_H__
#define __XE_GRAPHICS_MODELIO_H__

namespace xe::Graphics
{
	struct Model;
	namespace ModelIO
	{
		void SaveModel(std::filesystem::path filePath, const Model& model);
		void LoadModel(std::filesystem::path filePath, Model& model);
		void SaveMaterial(std::filesystem::path filePath, const Model& model);
		void LoadMaterial(std::filesystem::path filePath, Model& model);
		void SaveSkeleton(std::filesystem::path filePath, const Model& model);
		void LoadSkeleton(std::filesystem::path filePath, Model& model);

	}
}

#endif //__XE_GRAPHICS_MODELIO_H__