#include "Pch.h"
#include"ColliderComponent.h"

using namespace xe::Math;

void xe::ColliderComponent::Initialize()
{
	
}

void xe::ColliderComponent::Terminate()
{
	m_collisionShape.Termainate();
}

void xe::ColliderComponent::Serialize(YAML::Node& data)
{
	data["type"] = "ColliderComponent";
	data["shape"] = m_shapeData;
}

void xe::ColliderComponent::Deserialize(const yaml_val& data)
{
	const YAML::Node& shape = data["shape"];
	m_shapeData = data["shape"];

	const std::string type = shape["type"].as<std::string>();
	if (type == "empty")
		m_collisionShape.InitializeEmpty();
	else if (type == "box")
	{
		Vector3 halfExtends;
		halfExtends.x = shape["half-extends"]["x"].as<float>();
		halfExtends.y = shape["half-extends"]["y"].as<float>();
		halfExtends.z = shape["half-extends"]["z"].as<float>();
		m_collisionShape.InitializeBox(halfExtends);
	}
	else if (type == "sphere")
	{
		float radius = shape["radius"].as<float>();
		m_collisionShape.InitializeSphere(radius);
	}
	else if (type == "hull")
	{
		Vector3 halfExtends;
		halfExtends.x = shape["half-extends"]["x"].as<float>();
		halfExtends.y = shape["half-extends"]["y"].as<float>();
		halfExtends.z = shape["half-extends"]["z"].as<float>();
		Vector3 origin;
		origin.x = shape["origin"]["x"].as<float>();
		origin.y = shape["origin"]["y"].as<float>();
		origin.z = shape["origin"]["z"].as<float>();
		m_collisionShape.InitializeHull(halfExtends, origin);
	}
}
