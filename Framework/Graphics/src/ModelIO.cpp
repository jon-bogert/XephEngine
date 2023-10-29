#include "Pch.h"
#include "ModelIO.h"

#include "Model.h"
#include "Animation.h"
#include "AnimationBuilder.h"

void xe::Graphics::AnimationIO::Write(FILE* file, const Animation& animation)
{
	uint32_t count = animation._positionKeys.size();
	fprintf_s(file, "PositionKeyCount: %i", count);
	for (auto& key : animation._positionKeys)
	{
		fprintf_s(file, "%f %f %f %f\n", key.time, key.key.x, key.key.y, key.key.z);
	}
	count = animation._rotationKeys.size();
	fprintf_s(file, "RotationKeyCount: %i", count);
	for (auto& key : animation._rotationKeys)
	{
		fprintf_s(file, "%f %f %f %f %f\n", key.time, key.key.x, key.key.y, key.key.z, key.key.w);
	}
	count = animation._scaleKeys.size();
	fprintf_s(file, "ScaleKeyCount: %i", count);
	for (auto& key : animation._scaleKeys)
	{
		fprintf_s(file, "%f %f %f %f\n", key.time, key.key.x, key.key.y, key.key.z);
	}
}

void xe::Graphics::AnimationIO::Read(FILE* file, Animation& animation)
{
	AnimationBuilder builder;
	uint32_t count = 0;
	float time = 0.f;
	fscanf_s(file, "PositionKeyCount: %i", &count);
	for (uint32_t key = 0 ; key < count; ++key)
	{
		xe::Math::Vector3 pos;
		fscanf_s(file, "%f %f %f %f\n", &time, &pos.x, &pos.y, &pos.z);
		builder.AddPositionKey(pos, time);
	}
	fscanf_s(file, "RotationKeyCount: %i", &count);
	for (uint32_t key = 0; key < count; ++key)
	{
		xe::Math::Quaternion rot;
		fscanf_s(file, "%f %f %f %f %f\n", &time, &rot.x, &rot.y, &rot.z, &rot.w);
		builder.AddRotationKey(rot, time);
	}
	fscanf_s(file, "ScaleKeyCount: %i", &count);
	for (uint32_t key = 0; key < count; ++key)
	{
		xe::Math::Vector3 sca;
		fscanf_s(file, "%f %f %f %f\n", &time, &sca.x, &sca.y, &sca.z);
		builder.AddScaleKey(sca, time);
	}

	animation = builder.Build();
}

void xe::Graphics::ModelIO::SaveModel(std::filesystem::path filePath, const Model& model)
{
	if (model.meshData.empty())
	{
		LOG("SaveModel -> No model data found");
		return;
	}

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (!file)
	{
		return;
	}

	const uint32_t meshCount = static_cast<uint32_t>(model.meshData.size());
	fprintf_s(file, "MeshCount: %d\n", meshCount);
	for (uint32_t i = 0; i < meshCount; ++i)
	{
		const Model::MeshData& meshData = model.meshData[i];
		fprintf_s(file, "Material Index: %d\n", meshData.materialIndex);

		const Mesh& mesh = meshData.mesh;
		const uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fprintf_s(file, "VertexCount: %d\n", vertexCount);

		for (const Vertex& v : mesh.vertices)
		{
			fprintf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				v.position.x, v.position.y, v.position.z,
				v.normal.x, v.normal.y, v.normal.z,
				v.tangent.x, v.tangent.y, v.tangent.z,
				v.uvCoord.x, v.uvCoord.y);
		}

		const uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fprintf_s(file, "Index Count: %d\n", indexCount);
		for (uint32_t n = 2; n < indexCount; ++n)
		{
			fprintf_s(file, "%d %d %d\n", mesh.indices[n - 2], mesh.indices[n - 1], mesh.indices[n]);
		}
	}

	fclose(file);
}

void xe::Graphics::ModelIO::LoadModel(std::filesystem::path filePath, Model& model)
{
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (!file)
	{
		return;
	}

	uint32_t meshCount = 0;
	fscanf_s(file, "MeshCount: %d\n", &meshCount);
	model.meshData.resize(meshCount);

	for (uint32_t i = 0; i < meshCount; ++i)
	{
		Model::MeshData& meshData = model.meshData[i];
		fscanf_s(file, "Material Index: %d\n", &meshData.materialIndex);

		Mesh& mesh = meshData.mesh;
		uint32_t vertexCount = static_cast<uint32_t>(mesh.vertices.size());
		fscanf_s(file, "VertexCount: %d\n", &vertexCount);
		mesh.vertices.resize(vertexCount);

		for (Vertex& v : mesh.vertices)
		{
			fscanf_s(file, "%f %f %f %f %f %f %f %f %f %f %f\n",
				&v.position.x, &v.position.y, &v.position.z,
				&v.normal.x, &v.normal.y, &v.normal.z,
				&v.tangent.x, &v.tangent.y, &v.tangent.z,
				&v.uvCoord.x, &v.uvCoord.y);
		}

		uint32_t indexCount = static_cast<uint32_t>(mesh.indices.size());
		fscanf_s(file, "Index Count: %d\n", &indexCount);
		mesh.indices.resize(indexCount);

		for (uint32_t n = 2; n < indexCount; ++n)
		{
			fscanf_s(file, "%d %d %d\n", &mesh.indices[n - 2], &mesh.indices[n - 1], &mesh.indices[n]);
		}
	}

	fclose(file);
}

void xe::Graphics::ModelIO::SaveMaterial(std::filesystem::path filePath, const Model& model)
{
	if (model.materialData.empty())
		return;

	filePath.replace_extension("material");

	FILE* file = nullptr;

	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
		return;

	uint32_t materialCount = static_cast<uint32_t>(model.materialData.size());
	fprintf_s(file, "Material Count: %d\n", materialCount);
	for (const Model::MaterialData& materialData : model.materialData)
	{
		const Material& m = materialData.material;
		fprintf_s(file, "%f %f %f %f\n", m.ambient.r, m.ambient.g, m.ambient.b, m.ambient.a);
		fprintf_s(file, "%f %f %f %f\n", m.diffuse.r, m.diffuse.g, m.diffuse.b, m.diffuse.a);
		fprintf_s(file, "%f %f %f %f\n", m.specular.r, m.specular.g, m.specular.b, m.specular.a);
		fprintf_s(file, "%f %f %f %f\n", m.emissive.r, m.emissive.g, m.emissive.b, m.emissive.a);
		fprintf_s(file, "Power; %f\n", m.power);

		fprintf_s(file, "%s\n", materialData.diffuseMapName.empty() ? "<none>" : materialData.diffuseMapName.c_str());
		fprintf_s(file, "%s\n", materialData.specularMapName.empty() ? "<none>" : materialData.specularMapName.c_str());
		fprintf_s(file, "%s\n", materialData.displMapName.empty() ? "<none>" : materialData.displMapName.c_str());
		fprintf_s(file, "%s\n", materialData.normalMapName.empty() ? "<none>" : materialData.normalMapName.c_str());

	}
	fclose(file);
}

void xe::Graphics::ModelIO::LoadMaterial(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("material");

	FILE* file = nullptr;

	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
		return;

	auto TryReadTextureName = [&](auto& filename)
	{
		char buffer[MAX_PATH]{};
		fscanf_s(file, "%s\n", &buffer, (uint32_t)sizeof(buffer));
		if (strcmp(buffer, "<none>") != 0)
		{
			filename = filePath.replace_filename(buffer).string();
		}
	};

	uint32_t materialCount = 0;
	fscanf_s(file, "Material Count: %d\n", &materialCount);
	model.materialData.resize(materialCount);
	for (Model::MaterialData& materialData : model.materialData)
	{
		const Material& m = materialData.material;
		fscanf_s(file, "%f %f %f %f\n", &m.ambient.r, &m.ambient.g, &m.ambient.b, &m.ambient.a);
		fscanf_s(file, "%f %f %f %f\n", &m.diffuse.r, &m.diffuse.g, &m.diffuse.b, &m.diffuse.a);
		fscanf_s(file, "%f %f %f %f\n", &m.specular.r, &m.specular.g, &m.specular.b, &m.specular.a);
		fscanf_s(file, "%f %f %f %f\n", &m.emissive.r, &m.emissive.g, &m.emissive.b, &m.emissive.a);
		fscanf_s(file, "Power; %f\n", &m.power);

		TryReadTextureName(materialData.diffuseMapName);
		TryReadTextureName(materialData.specularMapName);
		TryReadTextureName(materialData.displMapName);
		TryReadTextureName(materialData.normalMapName);
	}
	fclose(file);
}

void xe::Graphics::ModelIO::SaveSkeleton(std::filesystem::path filePath, const Model& model)
{
	if (model.skeleton == nullptr || model.skeleton->bones.empty())
	{
		return;
	}

	filePath.replace_extension("skeleton");
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
	{
		return;
	}

	auto WriteMatrix = [&file](const xe::Math::Matrix4& m)
	{
		fprintf_s(file, "%f %f %f %f\n", m._11, m._12, m._13, m._14);
		fprintf_s(file, "%f %f %f %f\n", m._21, m._22, m._23, m._24);
		fprintf_s(file, "%f %f %f %f\n", m._31, m._32, m._33, m._34);
		fprintf_s(file, "%f %f %f %f\n", m._41, m._42, m._43, m._44);
	};

	uint32_t boneCount = model.skeleton->bones.size();
	fprintf_s(file, "BoneCount: %i\n", boneCount);
	fprintf_s(file, "RootBone: %i\n", model.skeleton->root->index);
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		const Bone* boneData = model.skeleton->bones[i].get();
		fprintf_s(file, "BoneName: %s\n", boneData->name.c_str());
		fprintf_s(file, "BoneIndex: %i\n", boneData->index);
		fprintf_s(file, "BoneParentIndex: %i\n", boneData->parentIndex);

		uint32_t childCount = boneData->childrenIndices.size();
		fprintf_s(file, "BoneChildrenCount: %i\n", childCount);
		for (uint32_t c = 0; c < childCount; ++c)
		{
			fprintf_s(file, "%i\n", boneData->childrenIndices[c]);
		}

		WriteMatrix(boneData->offsetTransform);
		WriteMatrix(boneData->toParentTransform);
	}

	fclose(file);
}

void xe::Graphics::ModelIO::LoadSkeleton(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("skeleton");
	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
	{
		return;
	}

	auto ReadMatrix = [&file](const xe::Math::Matrix4& m)
	{
		fscanf_s(file, "%f %f %f %f\n", &m._11, &m._12, &m._13, &m._14);
		fscanf_s(file, "%f %f %f %f\n", &m._21, &m._22, &m._23, &m._24);
		fscanf_s(file, "%f %f %f %f\n", &m._31, &m._32, &m._33, &m._34);
		fscanf_s(file, "%f %f %f %f\n", &m._41, &m._42, &m._43, &m._44);
	};

	model.skeleton = std::make_unique<Skeleton>();

	uint32_t boneCount = 0;
	uint32_t rootIndex = 0;
	fscanf_s(file, "BoneCount: %i\n", &boneCount);
	fscanf_s(file, "RootBone: %i\n", &rootIndex);

	model.skeleton->bones.resize(boneCount);
	for (uint32_t i = 0; i < boneCount; ++i)
	{
		model.skeleton->bones[i] = std::make_unique<Bone>();
	}
	model.skeleton->root = model.skeleton->bones[rootIndex].get();

	for (uint32_t i = 0; i < boneCount; ++i)
	{
		Bone* boneData = model.skeleton->bones[i].get();

		uint32_t boneIndex = 0;
		char boneName[MAX_PATH]{};

		fscanf_s(file, "BoneName: %s\n", boneName, (uint32_t)sizeof(boneName));
		fscanf_s(file, "BoneIndex: %i\n", &boneData->index);
		fscanf_s(file, "BoneParentIndex: %i\n", &boneData->parentIndex);

		boneData->name = boneName;
		if (boneData->parentIndex > -1)
		{
			boneData->parent = model.skeleton->bones[boneData->parentIndex].get();
		}

		uint32_t childCount = 0;
		fscanf_s(file, "BoneChildrenCount: %i\n", &childCount);
		if (childCount > 0)
		{
			boneData->children.resize(childCount);
			boneData->childrenIndices.resize(childCount);
			for (uint32_t c = 0; c < childCount; ++c)
			{
				uint32_t childIndex = 0;
				fscanf_s(file, "%i\n", &childIndex);
				boneData->childrenIndices[c] = childIndex;
				boneData->children[c] = model.skeleton->bones[childIndex].get();
			}
		}

		ReadMatrix(boneData->offsetTransform);
		ReadMatrix(boneData->toParentTransform);
	}

	fclose(file);
}

void xe::Graphics::ModelIO::SaveAnimations(std::filesystem::path filePath, const Model& model)
{
	if (model.skeleton == nullptr || model.skeleton->bones.empty() || model.animationClips.empty())
		return;

	filePath.replace_extension("animset");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "w");
	if (file == nullptr)
	{
		return;
	}
	
	uint32_t animClipCount = model.animationClips.size();
	fprintf_s(file, "AnimClipCount: %i\n", animClipCount);
	for (uint32_t i = 0; i < animClipCount; ++i)
	{
		const AnimationClip& animClipData = model.animationClips[i];

		fprintf_s(file, "AnimClipName: %s\n", animClipData.name.c_str());
		fprintf_s(file, "FrameDuration: %f\n", animClipData.durationInFrames);
		fprintf_s(file, "FramesPerSecond: %f\n", animClipData.framesPerSecond);

		uint32_t boneAnimCount = animClipData.boneAnimations.size();
		fprintf_s(file, "BoneAnimCount: %i\n", boneAnimCount);
		for (uint32_t b = 0; b < boneAnimCount; ++b)
		{
			Animation* boneAnim = animClipData.boneAnimations[b].get();
			if (boneAnim == nullptr)
			{
				fprintf_s(file, "[EMPTY]\n");
				continue;
			}
			fprintf_s(file, "[ANIMATION]\n");
			AnimationIO::Write(file, *boneAnim);
		}
	}

	fclose(file);
}

void xe::Graphics::ModelIO::LoadAnimations(std::filesystem::path filePath, Model& model)
{
	filePath.replace_extension("animset");

	FILE* file = nullptr;
	fopen_s(&file, filePath.u8string().c_str(), "r");
	if (file == nullptr)
	{
		return;
	}

	uint32_t animClipCount = model.animationClips.size();
	fscanf_s(file, "AnimClipCount: %i\n", &animClipCount);
	for (uint32_t i = 0; i < animClipCount; ++i)
	{
		AnimationClip& animClipData = model.animationClips.emplace_back();

		char buffer[MAX_PATH];
		fscanf_s(file, "AnimClipName: %s\n", buffer, (uint32_t)sizeof(buffer));
		animClipData.name = std::move(buffer);
		fscanf_s(file, "FrameDuration: %f\n", &animClipData.durationInFrames);
		fscanf_s(file, "FramesPerSecond: %f\n", &animClipData.framesPerSecond);

		uint32_t boneAnimCount = 0;
		fscanf_s(file, "BoneAnimCount: %i\n", &boneAnimCount);
		animClipData.boneAnimations.resize(boneAnimCount);
		for (uint32_t b = 0; b < boneAnimCount; ++b)
		{
			char label[128];
			fscanf_s(file, "%s\n", label, (uint32_t)sizeof(label));
			if (strcmp(label, "[ANIMATION]") == 0)
			{
				animClipData.boneAnimations[b] = std::make_unique<Animation>();
				AnimationIO::Read(file, *animClipData.boneAnimations[b]);
			}
		}
	}

	fclose(file);
}
