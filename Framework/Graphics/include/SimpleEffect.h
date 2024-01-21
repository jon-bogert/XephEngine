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
		const Camera* _camera = nullptr;

		ConstantBuffer _constantBuffer;
		VertexShader _vertexShader;
		PixelShader _pixelShader;
		Sampler _sampler;

	public:
		void Initialize();
		void Terminate();

		void Begin();
		void Draw(const RenderObject& renderObject);
		void End();

		void SetCamera(const Camera& camera);
	};
}

#endif // XE_GRAPHICS_SIMPLEEFFECT_H
