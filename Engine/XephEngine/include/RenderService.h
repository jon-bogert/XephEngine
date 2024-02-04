#ifndef __XE_XEPHENGINE_RENDERSERVICE_H__
#define __XE_XEPHENGINE_RENDERSERVICE_H__

#include "Service.h"

namespace xe
{
	class CameraService;
	class ModelComponent;
	class MeshComponent;
	class TransformComponent;
	class RenderService final : public Service
	{
	public:
		SET_TYPE_ID(ServiceID::Render);

		void Initialize() override;
		void Terminate() override;
		void Update(const float deltaTime) override;
		void Draw() override;
		void DebugUI() override;

		void Deserialize(const yaml_val& data) override;

		void Register(const ModelComponent* modelComponent);
		void Unregister(const ModelComponent* modelComponent);

		void Register(const MeshComponent* modelComponent);
		void Unregister(const MeshComponent* modelComponent);

	private:
		const CameraService* m_cameraService = nullptr;

		Graphics::DirectionalLight m_directionalLight;
		Graphics::StandardEffect m_standardEffect;
		Graphics::ShadowEffect m_shadowEffect;

		float m_fps = 0.f;

		struct Entry
		{
			const ModelComponent* modelComponent = nullptr;
			const MeshComponent* meshComponent = nullptr;
			const TransformComponent* transformComponent = nullptr;
			Graphics::RenderGroup renderGroup;
		};
		using RenderEntities = std::vector<Entry>;
		RenderEntities m_renderEntries;
	};
}
#endif //!__XE_XEPHENGINE_RENDERSERVICE_H__
