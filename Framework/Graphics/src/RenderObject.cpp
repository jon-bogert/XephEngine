#include "Pch.h"
#include "RenderObject.h"
#include "Model.h"

void xe::Graphics::RenderObject::Terminate()
{
	diffuseMapID = 0;
	normalMapID = 0;
	displMapID = 0;
	specMapID = 0;
	meshBuffer.Terminate();
}

xe::Graphics::RenderGroup xe::Graphics::CreateRenderGroup(const xe::Graphics::Model& model)
{
	RenderGroup renderGroup;
	renderGroup.reserve(model.meshData.size());

	auto TryLoadTexture = [](const auto& textureName)->TextureID
	{
		if (textureName.empty())
		{
			return 0;
		}

		return TextureManager::LoadTexture(textureName, false);
	};

	for (const Model::MeshData& meshData : model.meshData)
	{
		RenderObject& renderObject = renderGroup.emplace_back();
		if (meshData.materialIndex < model.materialData.size())
		{
			const Model::MaterialData& materialData = model.materialData[meshData.materialIndex];
			renderObject.material = materialData.material;
			renderObject.diffuseMapID = TryLoadTexture(materialData.diffuseMapName);
			renderObject.specMapID = TryLoadTexture(materialData.specularMapName);
			renderObject.displMapID = TryLoadTexture(materialData.displMapName);
			renderObject.normalMapID = TryLoadTexture(materialData.normalMapName);
		}

		renderObject.meshBuffer.Initialize(meshData.mesh);
	}
	return renderGroup;
}

void xe::Graphics::CleanupRenderGroup(RenderGroup& renderGroup)
{
	for (RenderObject& renderObject : renderGroup)
	{
		renderObject.Terminate();
	}
}

