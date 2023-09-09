#ifndef __XE_GRAPHICS_TERRAINEFFECT_H__
#define __XE_GRAPHICS_TERRAINEFFECT_H__

#include "ConstantBuffer.h"
#include "LightType.h"
#include "Material.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Sampler.h"

namespace xe::Graphics
{
	class Camera;
	class Texture;
	class RenderObject;

	class TerrainEffect final
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
			int useShadowMap = 0;
			float depthBias = 0.f;
			float padding[2] = { 0 };
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
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void DebugUI();

		void SetCamera(const Camera& camera);
		void SetLightCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);
		void SetShadowMap(const Texture& shadowMap);
	};
}

#endif // __XE_GRAPHICS_TERRAINEFFECT_H__