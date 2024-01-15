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
	public:
		void Initialize(const std::filesystem::path&);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);
		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void DebugUI();

	private:
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

		TransformBuffer m_transformBuffer;
		LightingBuffer m_lightingBuffer;
		MaterialBuffer m_materialBuffer;
		SettingsBuffer m_settingsBuffer;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
		Sampler m_sampler;

		SettingsData m_settingsData;
		const Camera* m_camera = nullptr;
		const DirectionalLight* m_directionalLight = nullptr;
	};
}

#endif //!__XE_GRAPHICS_CELEFFECT_H__
