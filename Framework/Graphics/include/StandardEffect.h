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
			uint32_t __ { 0 };
		};

		using TransformBuffer = TypedContantBuffer<TransfromData>;
		using LightingBuffer = TypedContantBuffer<DirectionalLight>;
		using MaterialBuffer = TypedContantBuffer<Material>;
		using SettingsBuffer = TypedContantBuffer<SettingsData>;

		TransformBuffer _transformBuffer;
		LightingBuffer _lightingBuffer;
		MaterialBuffer _materialBuffer;
		SettingsBuffer _settingsBuffer;

		VertexShader _vertexShader;
		PixelShader _pixelShader;
		Sampler _sampler;

		SettingsData _settingsData;
		const Camera* _camera = nullptr;
		const Camera* _lightCamera = nullptr;
		const DirectionalLight* _directionalLight = nullptr;
		const Texture* _shadowMap = nullptr;

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
	};
}

#endif
