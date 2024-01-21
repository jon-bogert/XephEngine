#ifndef __XE_GRAPHICS_CEL_EFFECT_H__
#define __XE_GRAPHICS_CEL_EFFECT_H__

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

	class CelEffect
	{
		struct TransfromData
		{
			xe::Math::Matrix4 world;
			xe::Math::Matrix4 wvp;
			xe::Math::Vector3 viewPosition;
			uint32_t __ = 0; // 16-Byte Padding
		};
		struct SettingsData
		{
			int useDiffuseMap = 1;
			uint32_t __[3] = { 0 };
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
		const DirectionalLight* _directionalLight = nullptr;

	public:
		void Initialize(const std::filesystem::path&);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();
	};
}

#endif
