#include "Pch.h"
#include "MeshComponent.h"

#include "World.h"
#include "RenderService.h"

using namespace xe::Graphics;

void xe::MeshComponent::Initialize()
{
	RenderService* renderService = GetGameObject().GetWorld().GetService<RenderService>();
	renderService->Register(this);
}

void xe::MeshComponent::Terminate()
{
	RenderService* renderService = GetGameObject().GetWorld().GetService<RenderService>();
	renderService->Unregister(this);
}

void xe::MeshComponent::Deserialize(const yaml_val& data)
{
	Model::MeshData& meshData = m_model.meshData.emplace_back();
	Model::MaterialData& materialData = m_model.materialData.emplace_back();
	if (data["shape"].IsDefined())
	{
		std::string type = data["shape"]["type"].as<std::string>();
		if (type == "cube")
		{
			const float size = data["shape"]["size"].as<float>();
			ASSERT(false, "Need CreateCube Implemented");
			//meshData.mesh = MeshBuilder::CreateCube(size);
		}
		else if (type == "sphere")
		{
			const int slices = data["shape"]["slices"].as<int>();
			const int rings = data["shape"]["rings"].as<int>();
			const float radius = data["shape"]["radius"].as<float>();
			meshData.mesh = MeshBuilder::CreateUVSphere(slices, rings, radius);
		}
		else if (type == "plane")
		{
			const int rows = data["shape"]["rows"].as<int>();
			const int columns = data["shape"]["columns"].as<int>();
			const float spacing = data["shape"]["spacing"].as<float>();
			meshData.mesh = MeshBuilder::CreateGroundPlane(rows, columns, spacing);
		}
		else
		{
			ASSERT(false, "Shape type %s not defined", type.c_str());
		}
	}

	if (data["material"].IsDefined())
	{
		materialData.material.ambient.r = data["material"]["ambient"]["r"].as<float>();
		materialData.material.ambient.g = data["material"]["ambient"]["g"].as<float>();
		materialData.material.ambient.b = data["material"]["ambient"]["b"].as<float>();
		materialData.material.ambient.a = data["material"]["ambient"]["a"].as<float>();

		materialData.material.diffuse.r = data["material"]["diffuse"]["r"].as<float>();
		materialData.material.diffuse.g = data["material"]["diffuse"]["g"].as<float>();
		materialData.material.diffuse.b = data["material"]["diffuse"]["b"].as<float>();
		materialData.material.diffuse.a = data["material"]["diffuse"]["a"].as<float>();

		materialData.material.specular.r = data["material"]["specular"]["r"].as<float>();
		materialData.material.specular.g = data["material"]["specular"]["g"].as<float>();
		materialData.material.specular.b = data["material"]["specular"]["b"].as<float>();
		materialData.material.specular.a = data["material"]["specular"]["a"].as<float>();

		materialData.material.emissive.r = data["material"]["emissive"]["r"].as<float>();
		materialData.material.emissive.g = data["material"]["emissive"]["g"].as<float>();
		materialData.material.emissive.b = data["material"]["emissive"]["b"].as<float>();
		materialData.material.emissive.a = data["material"]["emissive"]["a"].as<float>();

		materialData.material.power = data["material"]["power"].as<float>();
	}

	if (data["textures"].IsDefined())
	{
		if (data["textures"]["diffuse"].IsDefined())
		{
			materialData.diffuseMapName = data["textures"]["diffuse"].as<std::string>();
		}
		if (data["textures"]["normal"].IsDefined())
		{
			materialData.normalMapName = data["textures"]["normal"].as<std::string>();
		}
		if (data["textures"]["displ"].IsDefined())
		{
			materialData.displMapName = data["textures"]["displ"].as<std::string>();
		}
		if (data["textures"]["specular"].IsDefined())
		{
			materialData.specularMapName = data["textures"]["specular"].as<std::string>();
		}
	}

	if (data["cast-shadow"].IsDefined())
	{
		m_castShadow = data["cast-shadow"].as<bool>();
	}
}
