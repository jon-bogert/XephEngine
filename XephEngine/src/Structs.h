#pragma once

namespace xe
{
	struct Vector2
	{
		float x = 0.f;
		float y = 0.f;

		Vector2() = default;
		Vector2(float x, float y) : x(x), y(y) {};
		Vector2(int x, int y) : x(x), y(y) {};
	};
	typedef Vector2 Vector2f;

	struct Vector2i
	{
		int x = 0;
		int y = 0;

		Vector2i() = default;
		Vector2i(int x, int y) : x(x), y(y) {};
		Vector2i(float x, float y) : x(x), y(y) {};
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
		Vector2 postion;
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
}
