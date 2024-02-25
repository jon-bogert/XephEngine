#pragma once

#include "Component.h"

namespace xe
{
	class CameraComponent;
	class TransformComponent;
	class FPSCameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::FPSCamera);

		void Initialize() override;
		void Terminate() override;
		void Update(const float deltaTime) override;

		void Serialize(YAML::Node& data) override;
		void Deserialize(const yaml_val& data) override;

	private:
		TransformComponent* m_transformComponent = nullptr;
		CameraComponent* m_cameraComponent = nullptr;
		float m_moveSpeed = 2.f;
		float m_turnSpeed = 0.1f;
		float m_shiftSpeed = 10.f;
	};
}