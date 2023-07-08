#ifndef __XE_GRAPHICS_STANDARD_EFFECT_H__
#define __XE_GRAPHICS_STANDARD_EFFECT_H__

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "VertexShader.h"


namespace xe::Graphics
{
	class Camera;
	class RenderObject;
	class Texture;

	class StandardEffect
	{
		ConstantBuffer _transformBuffer;
		VertexShader _vertexShader;
		PixelShader _pixelShader;
		Sampler _sampler;

		const Camera* _camera = nullptr;

	public:
		void Initialize(const std::filesystem::path&);
		void Terminate();

		void Begin();
		void End();

		void Draw(const RenderObject& renderObject);

		void SetCamera(const Camera& camera);

		void DebugUI();
	};
}

#endif
