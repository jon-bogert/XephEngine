#include "Math.h"

xe::Vector2 xe::Math::ForwardVector(float theta)
{
	theta *= 3.14159 / 180;
	return Vector2(sinf(theta), cosf(theta));
}
