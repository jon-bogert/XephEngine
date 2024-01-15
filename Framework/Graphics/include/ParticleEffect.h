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
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObj);

		void DebugUI();
		void SetCamera(const Camera& camera);

	private:
		struct TransformData
		{
			xe::Math::Matrix4 wvp;
		};
		using TransformBuffer = TypedContantBuffer<TransformData>;
		TransformBuffer m_transformBuffer;

		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
		BlendState m_blendState;

		const Camera* m_camera = nullptr;
	};
}


#endif //!__XE_GRAPHICS_PARTICLEEFFECT_H__