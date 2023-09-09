#ifndef __XE_GRAPHICS_SSAOEFFECT_H__
#define __XE_GRAPHICS_SSAOEFFECT_H__

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"
#include "Sampler.h"

namespace xe::Graphics
{
	class RenderObject;
	class SSAOEffect final
	{
		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer _transformBuffer;

		struct SettingsData
		{
			float sampleRadius = 0.5f;
			uint32_t useSSAO = 1;
			uint32_t __[2] = { 0 };
		};
		using SettingsBuffer = TypedContantBuffer<SettingsData>;
		SettingsBuffer _settingsBuffer;
		SettingsData _settingsData;

		VertexShader _vertexShader;
		PixelShader _pixelShader;
		Sampler _sampler;

		const Camera* _camera;
		//RenderTarget _renderTarget;

		const Texture* _depthTexture = nullptr;

	public:
		void Initialize(Camera& camera, const Texture& depthTexture);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		//const Texture& GetDephtMap() const { return _renderTarget; }
	};
}

#endif // __XE_GRAPHICS_SSAOEFFECT_H__