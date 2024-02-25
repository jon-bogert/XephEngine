#include "Pch.h"
#include "ModelComponent.h"

#include "RenderService.h"
#include "World.h"

using namespace xe::Graphics;

void xe::ModelComponent::Initialize()
{
	m_modelID = ModelManager::GetModelID(m_fileName);
	if (ModelManager::GetModel(m_modelID) == nullptr)
	{
		if (m_modelID != 0)
		{
			m_modelID = ModelManager::LoadModel(m_fileName);
			for (const std::string& filename : m_animations)
			{
				ModelManager::AddAnimation(m_modelID, filename);
			}
		}
	}

	RenderService* renderService = GetGameObject().GetWorld().GetService<RenderService>();
	renderService->Register(this);
}

void xe::ModelComponent::Terminate()
{
	RenderService* renderService = GetGameObject().GetWorld().GetService<RenderService>();
	renderService->Unregister(this);
}

void xe::ModelComponent::Serialize(YAML::Node& data)
{
	data["type"] = "ModelComponent";
	if (!m_fileName.empty())
	{
		data["file"] = m_fileName;
	}
	if (!m_animations.empty())
	{
		YAML::Node animations = data["animations"];
		for (std::string& anim : m_animations)
		{
			animations.push_back(anim);
		}
	}
	data["cast-shadow"] = m_castShadow;
}

void xe::ModelComponent::Deserialize(const yaml_val& data)
{
	if (data["file"].IsDefined())
	{
		m_fileName = data["file"].as<std::string>();
	}
	if (data["animations"].IsDefined())
	{
		for (yaml_val animation : data["animations"])
		{
			m_animations.push_back(animation.as<std::string>());
		}
	}

	if (data["cast-shadow"].IsDefined())
	{
		m_castShadow = data["cast-shadow"].as<bool>();
	}
}
