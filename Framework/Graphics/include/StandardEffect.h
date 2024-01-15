#ifndef __XE_GRAPHICS_STANDARD_EFFECT_H__
#define __XE_GRAPHICS_STANDARD_EFFECT_H__

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"
#include "LightType.h"
#include "Material.h"


namespace xe::Graphics
{
	class Camera;
	class RenderObject;
	class Texture;

	class StandardEffect
	{
	public:
		void Initialize(const std::filesystem::path&);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetLightCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetShadowMap(const Texture& shadowMap);

		void DebugUI();

	private:
		struct TransfromData
		{
			xe::Math::Matrix4 world;
			xe::Math::Matrix4 wvp;
			xe::Math::Matrix4 lwvp; // ight wvp
			xe::Math::Vector3 viewPosition;
			uint32_t __ = 0; // 16-Byte Padding
		};
		struct SettingsData
		{
			int useDiffuseMap = 1;
			int useNormalMap = 1;
			int useDisplMap = 1;
			float displWeight = 1.f;
			int useSpecMap = 1;
			int useShadowMap = 1;
			float depthBias = 0.000042f;
			int useSkinning = 1;
		};

		using TransformBuffer = TypedContantBuffer<TransfromData>;
		using LightingBuffer = TypedContantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedContantBuffer<Material>;
		using SettingsBuffer = TypedContantBuffer<SettingsData>;
		using BoneTransformBuffer = ConstantBuffer;

		TransformBuffer m_transformBuffer;
		LightingBuffer m_lightingBuffer;
		MaterialBuffer m_materialBuffer;
		SettingsBuffer m_settingsBuffer;
		BoneTransformBuffer m_boneTransformBuffer;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
		Sampler m_sampler;

		SettingsData m_settingsData;
		const Camera* m_camera = nullptr;
		const Camera* m_lightCamera = nullptr;
		const DirectionalLight* m_directionalLight = nullptr;
		const Texture* m_shadowMap = nullptr;
	};
}

#endif //!__XE_GRAPHICS_STANDARDEFFECT_H__
