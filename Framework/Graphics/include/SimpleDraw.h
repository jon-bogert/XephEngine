#ifndef __XE_GRAPHICS_SIMPLEDRAW_H__
#define __XE_GRAPHICS_SIMPLEDRAW_H__

#include "Colors.h"

namespace xe::Graphics
{
	class Camera;

	namespace SimpleDraw
	{
		void Initialize(uint32_t maxVertexCount);
		void Terminate();
		void Draw(const Camera& camera);

		void AddLine(const xe::Math::Vector3& v0, const xe::Math::Vector3& v1, const xe::Color& color);
		void AddFace(const xe::Math::Vector3& v0, const xe::Math::Vector3& v1, const xe::Math::Vector3& v2, const xe::Color& color);

		void AddBoxWireframe(const xe::Math::Vector3& min, const xe::Math::Vector3& max, const xe::Color& color);
		void AddBoxWireframe(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const xe::Color& color);

		void AddBoxFilled(const xe::Math::Vector3& min, const xe::Math::Vector3& max, const xe::Color& color);
		void AddBoxFilled(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, const xe::Color& color);

		void AddSphere(uint32_t slices, uint32_t rings, float radius, const Color& color);
		void AddSphere(xe::Math::Vector3 origin, uint32_t slices, uint32_t rings, float radius, const Color& color);

		void AddGroundPlane(float size, const Color& color);
		void AddGroundCircle(uint32_t slices, float radius, const xe::Color& color);

		void AddTransfrom(const xe::Math::Matrix4& matrix);
	}
}

#endif // XE_GRAPHICS_SIMPLEDRAW_H

