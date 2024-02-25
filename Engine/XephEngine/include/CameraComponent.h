#ifndef __XE_XEPHENGINE_CAMERACOMPONENT_H__
#define __XE_XEPHENGINE_CAMERACOMPONENT_H__

#include "Component.h"

namespace xe
{
	class CameraComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::Camera);

		void Initialize() override;
		void Terminate() override;

		Graphics::Camera& GetCamera() { return m_camera; }
		const Graphics::Camera& GetCamera() const { return m_camera; }

		void Serialize(YAML::Node& data) override;
		void Deserialize(const yaml_val& data) override;

	private:
		Graphics::Camera m_camera;
	};
}

#endif // !__XE_XEPHENGINE_CAMERACOMPONENT_H__
