#include "Pch.h"
#include "ModelComponent.h"

#include "RenderService.h"
#include "World.h"

using namespace xe::Graphics;

void xe::ModelComponent::Initialize()
{
	m_modelID = ModelManager::LoadModel(m_fileName);
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
}
