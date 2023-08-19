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
		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer _transformBuffer;

		VertexShader _vertexShader;
		PixelShader _pixelShader;

		const DirectionalLight* _directionalLight = nullptr;

		Camera _lightCamera;
		RenderTarget _depthMapRenderTarget;

		xe::Math::Vector3 _focalPoint;
		float _size = 24.f;

	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		void SetDirectionalLight(const DirectionalLight& dirLight) { _directionalLight = &dirLight; };
		void SetFocalPoint(const xe::Math::Vector3& focalPnt) { _focalPoint = focalPnt; };
		void SetSize(const float size) { _size = size; }

		const Camera& GetLightCamera() const { return _lightCamera; }
		const Texture& GetDephtMap() const { return _depthMapRenderTarget; }

	private:
		void UpdateLightCamera();
	};
}

#endif // __XE_GRAPHICS_SHADOWEFFECT_H__
