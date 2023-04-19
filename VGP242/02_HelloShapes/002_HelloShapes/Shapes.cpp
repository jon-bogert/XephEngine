#include "Shapes.h"

using namespace xe;

void Triangle::CreateShape()
{
	_vertices.push_back({ {-0.5f, 0.0f, 0.0f}, Colors::Teal });
	_vertices.push_back({ {0.0f, 0.75f, 0.0f}, Colors::Red });
	_vertices.push_back({ {0.5f, 0.0f, 0.0f}, Colors::Green });
}

void Triangle::Update(const float& deltaTime)
{
	if (GetAsyncKeyState(VK_UP))
	{
		xe::MainApp().ChangeState("Square");
	}
}

void Square::CreateShape()
{
	_vertices.push_back({ {-0.5f, 0.0f, 0.0f}, Colors::Teal });
	_vertices.push_back({ {-0.5f, 0.75f, 0.0f}, Colors::Red });
	_vertices.push_back({ {0.5f, 0.0f, 0.0f}, Colors::Green });

	_vertices.push_back({ {-0.5f, 0.75f, 0.0f}, Colors::Teal });
	_vertices.push_back({ {0.5f, 0.75f, 0.0f}, Colors::Red });
	_vertices.push_back({ {0.5f, 0.0f, 0.0f}, Colors::Green });
}

void Square::Update(const float& deltaTime)
{
	if (GetAsyncKeyState(VK_DOWN))
	{
		xe::MainApp().ChangeState("Triangle");
	}
}
