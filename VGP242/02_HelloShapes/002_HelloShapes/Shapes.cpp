#include "Shapes.h"

using namespace xe;
using namespace xe::Input;

void Triangle::CreateShape()
{
	_vertices.push_back({ {-0.5f, 0.0f, 0.0f}, Colors::Teal });
	_vertices.push_back({ {0.0f, 0.75f, 0.0f}, Colors::Red });
	_vertices.push_back({ {0.5f, 0.0f, 0.0f}, Colors::Green });
}

void Triangle::Update(const float& deltaTime)
{
	if (InputSystem::Get().IsKeyPressed(Key::UP))
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
	if (InputSystem::Get().IsKeyPressed(Key::UP))
	{
		xe::MainApp().ChangeState("Triforce");
	}
	if (InputSystem::Get().IsKeyPressed(Key::DOWN))
	{
		xe::MainApp().ChangeState("Triangle");
	}
}

void Triforce::CreateShape()
{
	_vertices.push_back({ {-0.25f, 0.0f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {0.0f, 0.5f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {0.25f, 0.0f, 0.0f}, Colors::Yellow });


	_vertices.push_back({ {-0.5f, -0.5f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {-0.25f, 0.0f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {0.0f, -0.5f, 0.0f}, Colors::Yellow });


	_vertices.push_back({ {0.0f, -0.5f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {0.25f, 0.0f, 0.0f}, Colors::Yellow });
	_vertices.push_back({ {0.5f, -0.5f, 0.0f}, Colors::Yellow });
}

void Triforce::Update(const float& deltaTime)
{
	if (InputSystem::Get().IsKeyPressed(Key::DOWN))
	{
		xe::MainApp().ChangeState("Square");
	}

}
