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
}
