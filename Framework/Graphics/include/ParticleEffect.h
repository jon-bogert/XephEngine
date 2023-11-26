#ifndef __XE_GRAPHICS_PARTICLEEFFECT_H__
#define __XE_GRAPHICS_PARTICLEEFFECT_H__

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "BlendState.h"

namespace xe::Graphics
{
	class RenderObject;
	class Camera;
	class ParticleEffect
	{
		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer _transformBuffer;

		VertexShader _vertexShader;
		PixelShader _pixelShader;
		BlendState _blendState;

		const Camera* _camera = nullptr;

	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		void SetCamera(const Camera& camera);
	};
}


#endif //__XE_GRAPHICS_PARTICLEEFFECT_H__