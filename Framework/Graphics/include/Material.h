#pragma once

#include "Colors.h"

namespace xe::Graphics
{
	struct Material
	{
		Color ambient = Colors::White;
		Color diffuse = Colors::White;
		Color specular = Colors::White;
		Color emissive = Colors::Black;
		float power = 10.f;
		float normalMapIntensity = 1.f;
		uint32_t __[2] = { 0 };
	};
}