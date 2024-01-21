#ifndef __XE_GRAPHICS_LIGHTTYPE_H__
#define __XE_GRAPHICS_LIGHTTYPE_H__

#include "Colors.h"

namespace xe::Graphics
{
	struct DirectionalLight
	{
		xe::Color ambient = xe::Colors::DarkGray;
		xe::Color diffuse = xe::Colors::Gray;
		xe::Color specular = xe::Colors::White;
		xe::Math::Vector3 direction = xe::Math::Vector3::ZAxis;
		uint32_t __ = 0;
	};
}

#endif // __XE_GRAPHICS_LIGHTTYPE_H__
