#pragma once
#include "../Libraries.h"

namespace xe
{
	class GameObject;
	class Scene;

	struct Vector2
	{
		float x = 0.f;
		float y = 0.f;

		Vector2() = default;
		Vector2(float x, float y) : x(x), y(y) {};
		Vector2(int x, int y) : x(x), y(y) {};

		friend std::ostream& operator<<(std::ostream& os, const Vector2& v2)
		{
			os << "X:" << v2.x << ", Y:" << v2.y;
			return os;
		}
	};
	typedef Vector2 Vector2f;

	struct Vector2i
	{
		int x = 0;
		int y = 0;

		Vector2i() = default;
		Vector2i(int x, int y) : x(x), y(y) {};
		Vector2i(float x, float y) : x(x), y(y) {};

		friend std::ostream& operator<<(std::ostream& os, const Vector2i& v2)
		{
			os << "X:" << v2.x << ", Y:" << v2.y;
			return os;
		}
	};

	template <class T>
	struct Vector2T
	{
		T x;
		T y;

		Vector2T() = default;
		Vector2T(T x, T y) : x(x), y(y) {}
	};

	class Rotator
	{
		float value = 0.f;
		void Fix()
		{
			if(value >= 360.f)
			{
				value -= 360.f;
				Fix();
			}
			else if(value < 0.f)
			{
				value += 360.f;
				Fix();
			}
		}

	public:
		Rotator() = default;
		Rotator(float value) : value(value)
		{
			Fix();
		}
		void Add(const float amt)
		{
			value += amt;
			Fix();
		}
		void Subtract(const float amt)
		{
			value -= amt;
			Fix();
		}
		void Set(const float newValue)
		{
			value = newValue;
			Fix();
		}
		float GetRotation() const
		{
			return value;
		}
	};
	struct Transform
	{
		Vector2 position;
		Rotator rotation;
		Vector2 scale = {1.f, 1.f};
	};

	struct Rectangle
	{
		float x = 0.f;
		float y = 0.f;
		float width = 0.f;
		float height = 0.f;

		Rectangle() = default;
		Rectangle(float x, float y, float width, float height)
			:x(x), y(y), width(width), height(height) {}

		float GetRight()
		{
			return x + width;
		}
		float GetBottom()
		{
			return y + height;
		}
	};

	struct Color
	{
		int r = 255;
		int g = 255;
		int b = 255;
		int a = 255;

		Color() = default;
		Color(int r, int g, int b) : r(r), g(g), b(b) {}
		Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

		void Transparent() { a = 0; }
		void Opaque() { a = 255; }
		void Translucent() { a = 127; }
		void Sample(const Color newColor, bool keepOpacity = true)
		{
			r = newColor.r;
			g = newColor.g;
			b = newColor.b;
			if (!keepOpacity) a = newColor.a;
		}
	};
	typedef Color Colour;
}
