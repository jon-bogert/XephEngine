#ifndef __XE_GRAPHICS_DEPTHEFFECT_H__
#define __XE_GRAPHICS_DEPTHEFFECT_H__

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "RenderTarget.h"

namespace xe::Graphics
{
	class RenderObject;
	class DepthEffect final
	{
		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer _transformBuffer;

		VertexShader _vertexShader;
		PixelShader _pixelShader;

		//const DirectionalLight* _directionalLight = nullptr;

		const Camera* _camera;
		RenderTarget _depthMapRenderTarget;

	public:
		void Initialize(Camera& camera);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		//void SetDirectionalLight(const DirectionalLight& dirLight) { _directionalLight = &dirLight; };
		//void SetFocalPoint(const xe::Math::Vector3& focalPnt) { _focalPoint = focalPnt; };
		//void SetSize(const float size) { _size = size; }

		//const Camera& GetCamera() const { return _camera; }
		const Texture& GetDephtMap() const { return _depthMapRenderTarget; }
	};
}

#endif // __XE_GRAPHICS_DEPTHEFFECT_H__