#ifndef __XE_GRAPHICS_SHADOWEFFECT_H__
#define __XE_GRAPHICS_SHADOWEFFECT_H__

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"

namespace xe::Graphics
{
	class RenderObject;
	class ShadowEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		void SetDirectionalLight(const DirectionalLight& dirLight) { m_directionalLight = &dirLight; };
		void SetFocalPoint(const xe::Math::Vector3& focalPnt) { m_focalPoint = focalPnt; };
		void SetSize(const float size) { m_size = size; }

		const Camera& GetLightCamera() const { return m_lightCamera; }
		const Texture& GetDephtMap() const { return m_depthMapRenderTarget; }

	private:
		void UpdateLightCamera();

		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer m_transformBuffer;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;

		const DirectionalLight* m_directionalLight = nullptr;

		Camera m_lightCamera;
		RenderTarget m_depthMapRenderTarget;

		xe::Math::Vector3 m_focalPoint;
		float m_size = 24.f;
	};
}

#endif //!__XE_GRAPHICS_SHADOWEFFECT_H__
