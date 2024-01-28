#ifndef __XE_XEPHENGINE_CAMERASERVICE_H__
#define __XE_XEPHENGINE_CAMERASERVICE_H__

#include "Service.h"

namespace xe
{
	class CameraComponent;
	class CameraService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceID::Camera);

		void DebugUI() override;

		const Graphics::Camera& Main() const;

		void SetMainCamera(const uint32_t index);

	private:
		friend class CameraComponent;
		void Register(const CameraComponent* cameraComponent);
		void Unregister(const CameraComponent* cameraComponent);

		using CameraEntries = std::vector<const CameraComponent*>;
		CameraEntries m_cameraEntries;
		const CameraComponent* m_mainCamera = nullptr;
	};
}

#endif //!__XE_XEPHENGINE_CAMERASERVICE_H__