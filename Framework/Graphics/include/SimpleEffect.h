#ifndef __XE_GRAPHICS_SIMPLEEFFECT_H__
#define __XE_GRAPHICS_SIMPLEEFFECT_H__

#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "Sampler.h"
#include "PixelShader.h"

namespace xe::Graphics
{
	class Camera;
	class RenderObject;

	class SimpleEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void Draw(const RenderObject& renderObject);
		void End();

		void SetCamera(const Camera& camera);

	private:
		const Camera* m_camera = nullptr;

		ConstantBuffer m_constantBuffer;
		VertexShader m_vertexShader;
		PixelShader m_pixelShader;
		Sampler m_sampler;
	};
}

#endif //!__XE_GRAPHICS_SIMPLEEFFECT_H__
