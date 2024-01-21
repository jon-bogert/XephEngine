#include "Pch.h"
#include "TransformComponent.h"

void xe::TransformComponent::DebugUI()
{
	Graphics::SimpleDraw::AddTransfrom(Matrix());
}

void xe::TransformComponent::Deserialize(const yaml_val& data)
{
	position.x = data["position"]["x"].as<float>();
	position.y = data["position"]["y"].as<float>();
	position.z = data["position"]["z"].as<float>();

	rotation.x = data["rotation"]["x"].as<float>();
	rotation.y = data["rotation"]["y"].as<float>();
	rotation.z = data["rotation"]["z"].as<float>();
	rotation.w = data["rotation"]["w"].as<float>();

	scale.x = data["scale"]["x"].as<float>();
	scale.y = data["scale"]["y"].as<float>();
	scale.z = data["scale"]["z"].as<float>();
}
