#include <XephEngine/include/XephEngine.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

using namespace xe;
using namespace xe::Graphics;
using namespace xe::Math; 

using BoneIndexLookup = std::map <std::string, uint32_t>;

namespace stdfs = std::filesystem;

struct Arguments
{
	stdfs::path inputFilename;
	stdfs::path outputFilename;
	float scale = 1.f;
};

std::optional<Arguments> ParseArgs(int argc, char* argv[])
{
	if (argc < 3)
	{
		return std::nullopt;
	}

	Arguments args;
	args.inputFilename = argv[argc - 2];
	args.outputFilename = argv[argc - 1];

	for (int i = 1; i + 2 < argc; ++i)
	{
		if (strcmp(argv[i], "-scale") == 0)
		{
			args.scale = atof(argv[i + 1]);
			++i;
		}
	}

	return args;
}

Vector3 ToVector3(aiVector3D v)
{
	return { static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z) };
}

Quaternion ToQuaternion(aiQuaternion q)
{
	return { static_cast<float>(q.x), static_cast<float>(q.y), static_cast<float>(q.z), static_cast<float>(q.w) };
}

Color ToColor(aiColor3D c)
{
	return { static_cast<float>(c.r), static_cast<float>(c.g), static_cast<float>(c.b), 1.f};
}

Matrix4 ToMatrix4(const aiMatrix4x4& m)
{
	return {
		static_cast<float>(m.a1),static_cast<float>(m.b1),static_cast<float>(m.c1),static_cast<float>(m.d1),
		static_cast<float>(m.a2),static_cast<float>(m.b2),static_cast<float>(m.c2),static_cast<float>(m.d2),
		static_cast<float>(m.a3),static_cast<float>(m.b3),static_cast<float>(m.c3),static_cast<float>(m.d3),
		static_cast<float>(m.a4),static_cast<float>(m.b4),static_cast<float>(m.c4),static_cast<float>(m.d4)
	};
}

void ExportEmbeddedTexture(const aiTexture* texture, const Arguments& args, const stdfs::path filename)
{
	std::cout << "Extracting embedded texture" << std::endl;
	std::string fullFilename = args.outputFilename.u8string();
	fullFilename = fullFilename.substr(0, fullFilename.rfind('/') + 1);
	fullFilename += filename.filename().u8string();

	FILE* file = nullptr;
	errno_t err = fopen_s(&file, fullFilename.c_str(), "wb");
	if (err != 0 || !file)
	{
		std::cout << "ERROR: failed to open file " << fullFilename << " for saving" << std::endl;
		return;
	}

	size_t written = fwrite(texture->pcData, 1, texture->mWidth, file);
	ASSERT(written == texture->mWidth, "ERROR: failed to extract embedded texture");
	fclose(file);
}

std::string FindTexture(const aiScene* scene, const aiMaterial* aiMaterial, aiTextureType textureType, const Arguments& args, const std::string& suffix, uint32_t materialIndex)
{
	const uint32_t textureCount = aiMaterial->GetTextureCount(textureType);
	if (textureCount == 0)
	{
		return std::string();
	}


	stdfs::path textureName;
	aiString texturePath;
	if (aiMaterial->GetTexture(textureType, 0, &texturePath) == aiReturn_SUCCESS)
	{
		if (texturePath.C_Str()[0] == '*')
		{
			std::string filename = args.inputFilename.u8string();
			filename.erase(filename.length() - 4);
			filename += suffix;
			filename += texturePath.C_Str()[1];

			ASSERT(scene->HasTextures(), "Error: NO embedded texture found!");

			int textureIndex = atoi(texturePath.C_Str() + 1);
			ASSERT(textureIndex < scene->mNumTextures, "ERROR: Invelid texture index");

			const aiTexture* embeddedTexture = scene->mTextures[textureIndex];
			ASSERT(embeddedTexture->mHeight == 0, "ERROR: Uncompressed texture found!");

			if (embeddedTexture->CheckFormat("jpg"))
			{
				filename += ".jpg";
			}
			if (embeddedTexture->CheckFormat("png"))
			{
				filename += ".png";
			}
			else
			{
				ASSERT(false, "ERROR: Unrecognized texture format!");
			}

			ExportEmbeddedTexture(embeddedTexture, args, filename);

			std::cout << "Adding Texture " << filename << std::endl;
		}
		else if (const aiTexture* embeddedTexture = scene->GetEmbeddedTexture(texturePath.C_Str()); embeddedTexture)
		{
			stdfs::path embeddedFilePath = texturePath.C_Str();
			std::string filename = args.inputFilename.u8string();
			filename.erase(filename.length() - 4);
			filename += suffix;
			filename += "_" + std::to_string(materialIndex);
			filename += embeddedFilePath.extension().u8string();

			ExportEmbeddedTexture(embeddedTexture, args, filename);

			std::cout << "Adding Texture " << filename.c_str() << std::endl;
			textureName = filename;
		}
		else
		{
			stdfs::path filePath = texturePath.C_Str();
			std::string filename = filePath.filename().u8string();
			std::cout << "Adding Texture " << filename.c_str() << std::endl;
			textureName = filename;
		}
	}

	return textureName.filename().u8string();
}

Bone* BuildSkeleton(const aiNode& sceneNode, Bone* parent, Skeleton& skeleton, BoneIndexLookup& boneIndexLookup)
{
	Bone* bone = nullptr;
	std::string boneName = sceneNode.mName.C_Str();
	auto iter = boneIndexLookup.find(boneName);
	if (iter != boneIndexLookup.end())
	{
		bone = skeleton.bones[iter->second].get();
	}
	else
	{
		bone = skeleton.bones.emplace_back(std::make_unique<Bone>()).get();
		bone->index = static_cast<int> (skeleton.bones.size()) - 1;
		bone->offsetTransform = Matrix4::Identity;
		if (boneName.empty())
		{
			bone->name = "NoName" + std::to_string(bone->index);
		}
		else
		{
			bone->name = std::move(boneName);
		}
		boneIndexLookup.emplace(bone->name, bone->index);
	}

	if (skeleton.root == nullptr && parent == nullptr)
	{
		skeleton.root = bone;
	}

	bone->parent = parent;
	bone->parentIndex = parent ? parent->index : -1;
	bone->toParentTransform = ToMatrix4(sceneNode.mTransformation);

	bone->children.reserve(sceneNode.mNumChildren);
	for (uint32_t i = 0; i < sceneNode.mNumChildren; ++i)
	{
		Bone* child = BuildSkeleton(*(sceneNode.mChildren[i]), bone, skeleton, boneIndexLookup);
		bone->children.push_back(child);
		bone->childrenIndices.push_back(child->index);
	}

	return bone;
}

uint32_t GetBoneIndex(const aiBone* nodeBone, const BoneIndexLookup& boneIndexLookup)
{
	std::string boneName = nodeBone->mName.C_Str();
	ASSERT(!boneName.empty(), "ERROR: aiBone does not have a name");
	auto iter = boneIndexLookup.find(boneName);
	ASSERT(iter != boneIndexLookup.end(), "ERROR: aiBone was not found in the index map");
	return iter->second;
}

Bone* SetBoneOffsetTransform(const aiBone* nodeBone, Skeleton& skeleton, BoneIndexLookup& boneIndexLookup)
{
	uint32_t boneIndex = GetBoneIndex(nodeBone, boneIndexLookup);
	Bone* bone = skeleton.bones[boneIndex].get();
	bone->offsetTransform = ToMatrix4(nodeBone->mOffsetMatrix);
	return bone;
}

int main(int argc, char* argv[])
{
	const std::optional<Arguments> argOpt = ParseArgs(argc, argv);
	if (!argOpt)
	{
		std::cout << "No arguments to import fbx model" << std::endl;
		return 1;
	}

	const Arguments& args = *argOpt;
	Assimp::Importer importer;
	const uint32_t flags = aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded;

	const aiScene* scene = importer.ReadFile(args.inputFilename.u8string(), flags);
	if (!scene)
	{
		std::cout << "Error: " << importer.GetErrorString();
		return 1;
	}

	std::cout << "Importing " << args.inputFilename.u8string() << "..." << std::endl;

	Model model;
	BoneIndexLookup boneIndexLookup;

	if (scene->HasMeshes())
	{
		printf("Build skeleton...\n");

		model.skeleton = std::make_unique<Skeleton>();
		BuildSkeleton(*scene->mRootNode, nullptr, *model.skeleton, boneIndexLookup);
		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			const aiMesh* mesh = scene->mMeshes[meshIndex];
			if (mesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				continue;
			}
			if (mesh->HasBones())
			{
				for (uint32_t b = 0; b < mesh->mNumBones; ++b)
				{
					const aiBone* bone = mesh->mBones[b];
					SetBoneOffsetTransform(bone, *model.skeleton, boneIndexLookup);
				}
			}
		}
		for (std::unique_ptr<Bone>& bone : model.skeleton->bones)
		{
			bone->offsetTransform._41 *= args.scale;
			bone->offsetTransform._42 *= args.scale;
			bone->offsetTransform._43 *= args.scale;
			bone->offsetTransform._41 *= args.scale;
			bone->toParentTransform._41 *= args.scale;
			bone->toParentTransform._42 *= args.scale;
			bone->toParentTransform._43 *= args.scale;
		}


		std::cout << "Reading Mesh Data..." << std::endl;
		for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			const aiMesh* aiMesh = scene->mMeshes[meshIndex];
			if (aiMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE)
			{
				continue;
			}

			const uint32_t numVertices = aiMesh->mNumVertices;
			const uint32_t numFaces = aiMesh->mNumFaces;
			const uint32_t numIndices = numFaces * 3;

			Model::MeshData& meshData = model.meshData.emplace_back();

			std::cout << "Reading Material Index..." << std::endl;
			meshData.materialIndex = aiMesh->mMaterialIndex;

			std::cout << "Reading vertices..." << std::endl;

			Mesh& mesh = meshData.mesh;
			mesh.vertices.reserve(numVertices);

			const aiVector3D* positions = aiMesh->mVertices;
			const aiVector3D* normals = aiMesh->mNormals;
			const aiVector3D* tangents = aiMesh->HasTangentsAndBitangents() ? aiMesh->mTangents : nullptr;
			const aiVector3D* texCoords = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0] : nullptr;
			for (uint32_t v = 0; v < numVertices; ++v)
			{
				Vertex& vertex = mesh.vertices.emplace_back();
				vertex.position = ToVector3(positions[v]) * args.scale;
				vertex.normal = ToVector3(normals[v]);
				vertex.tangent = tangents ? ToVector3(tangents[v]) : Vector3::Zero;
				if (texCoords)
				{
					vertex.uvCoord = { texCoords[v].x, texCoords[v].y };
				}
			}

			std::cout << "Reading indices..." << std::endl;
			mesh.indices.reserve(numIndices);
			const auto& aiFaces = aiMesh->mFaces;
			for (uint32_t i = 0; i < numFaces; ++i)
			{
				const aiFace& aiFace = aiFaces[i];
				mesh.indices.push_back(aiFace.mIndices[0]);
				mesh.indices.push_back(aiFace.mIndices[1]);
				mesh.indices.push_back(aiFace.mIndices[2]);
			}
		}
	}
	if (scene->HasMaterials())
	{
		std::cout << "Reading Material Data....\n" << std::endl;

		const uint32_t numMaterials = scene->mNumMaterials;
		model.materialData.reserve(numMaterials);
		for (uint32_t materialIndex = 0; materialIndex < numMaterials; ++materialIndex)
		{
			const aiMaterial* aiMaterial = scene->mMaterials[materialIndex];
			aiColor3D ambient, diffuse, emissive, specular;
			ai_real specularPower = 1.f;

			aiMaterial->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			aiMaterial->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
			aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			aiMaterial->Get(AI_MATKEY_SHININESS, specularPower);

			Model::MaterialData& materialData = model.materialData.emplace_back();
			materialData.material.ambient = ToColor(ambient);
			materialData.material.diffuse = ToColor(diffuse);
			materialData.material.emissive = ToColor(emissive);
			materialData.material.specular = ToColor(specular);

			materialData.material.power = specularPower;

			materialData.diffuseMapName = FindTexture(scene, aiMaterial, aiTextureType_DIFFUSE, args, "_diffuse", materialIndex);
			materialData.normalMapName = FindTexture(scene, aiMaterial, aiTextureType_NORMALS, args, "_normal", materialIndex);
			materialData.displMapName = FindTexture(scene, aiMaterial, aiTextureType_DISPLACEMENT, args, "_displacement", materialIndex);
			materialData.specularMapName = FindTexture(scene, aiMaterial, aiTextureType_SPECULAR, args, "_specular", materialIndex);
		}
	}

	if (scene->HasAnimations())
	{
		std::cout << "Building Animations..." << std::endl;
		for (uint32_t animIndex = 0; animIndex < scene->mNumAnimations; ++animIndex)
		{
			const aiAnimation* aiAnim = scene->mAnimations[animIndex];
			AnimationClip& animClip = model.animationClips.emplace_back();
			if (aiAnim->mName.length > 0)
			{
				animClip.name = aiAnim->mName.C_Str();
			}
			else
			{
				animClip.name = "Anim" + std::to_string(animIndex);
			}
			animClip.durationInFrames = static_cast<float>(aiAnim->mDuration);
			animClip.framesPerSecond = static_cast<float>(aiAnim->mTicksPerSecond);

			std::cout << "Reading bone animations for " << animClip.name << "..." << std::endl;
			animClip.boneAnimations.resize(model.skeleton->bones.size());
			for (uint32_t boneAnimIndex = 0; boneAnimIndex < aiAnim->mNumChannels; ++boneAnimIndex)
			{
				const aiNodeAnim* aiBoneAnim = aiAnim->mChannels[boneAnimIndex];
				const int boneIndex = boneIndexLookup[aiBoneAnim->mNodeName.C_Str()];
				std::unique_ptr<Animation>& boneAnimation = animClip.boneAnimations[boneIndex];
				boneAnimation = std::make_unique<Animation>();

				AnimationBuilder builder;
				for (uint32_t keyIndex = 0; keyIndex < aiBoneAnim->mNumPositionKeys; ++keyIndex)
				{
					aiVectorKey& posKey = aiBoneAnim->mPositionKeys[keyIndex];
					builder.AddPositionKey(ToVector3(posKey.mValue)* args.scale, static_cast<float>(posKey.mTime));
				}
				for (uint32_t keyIndex = 0; keyIndex < aiBoneAnim->mNumRotationKeys; ++keyIndex)
				{
					aiQuatKey& rotKey = aiBoneAnim->mRotationKeys[keyIndex];
					builder.AddRotationKey(ToQuaternion(rotKey.mValue), static_cast<float>(rotKey.mTime));
				}
				for (uint32_t keyIndex = 0; keyIndex < aiBoneAnim->mNumScalingKeys; ++keyIndex)
				{
					aiVectorKey& scaleKey = aiBoneAnim->mScalingKeys[keyIndex];
					builder.AddScaleKey(ToVector3(scaleKey.mValue), static_cast<float>(scaleKey.mTime));
				}
				*boneAnimation = builder.Build();
			}
		}
	}

	std::cout << "Saving Model..." << std::endl;
	ModelIO::SaveModel(args.outputFilename, model);
	
	std::cout << "Saving Material..." << std::endl;
	ModelIO::SaveMaterial(args.outputFilename, model);

	std::cout << "Saving Skeleton..." << std::endl;
	ModelIO::SaveSkeleton(args.outputFilename, model);

	std::cout << "Saving Animations..." << std::endl;
	ModelIO::SaveAnimations(args.outputFilename, model);

	std::cout << "All Completed!" << std::endl;


	return 0;
}