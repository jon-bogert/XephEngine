#include "InputSystem.h"
#include "Application.h"
#include "Window.h"
#include "Libraries.h"

sf::Event inputEvent;

bool xe::InputSystem::Update()
{
	return Engine::GetWindow()->UnWrap()->pollEvent(inputEvent);
}

bool xe::InputSystem::CloseWindow()
{
	return (inputEvent.type == sf::Event::Closed);
}

bool xe::InputSystem::KeyDown(const Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}
