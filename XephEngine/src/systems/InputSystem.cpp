#include "InputSystem.h"

sf::Event inputEvent;

std::vector<xe::Key> keyHold;

bool xe::InputSystem::Update()
{
	return Engine::GetWindow()->UnWrap()->pollEvent(inputEvent);
}

bool xe::InputSystem::CloseWindow()
{
	return (inputEvent.type == sf::Event::Closed);
}

bool xe::InputSystem::KeyHold(const Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

bool xe::InputSystem::KeyPress(const Key key)
{
	bool keyFound{};
	int index{};
	for (xe::Key k : keyHold)
	{
		if (k == key)
		{
			keyFound = true;
			break;
		}
		else index++;
	}

	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key))
	{
		if (!keyFound)
		{
			keyHold.push_back(key);
			return true;
		}
	}
	else if (keyFound)
		keyHold.erase(keyHold.begin() + index);

	return false;
}

void xe::InputSystem::Typing(std::string& out_str)
{
	if (KeyPress(Key::Backspace) && out_str.size() > 0)
	{
		out_str.pop_back();
		return;
	}

	char c = 0;
	if (KeyPress(Key::A)) c = 'a';
	else if (KeyPress(Key::B)) c = 'b';
	else if (KeyPress(Key::C)) c = 'c';
	else if (KeyPress(Key::D)) c = 'd';
	else if (KeyPress(Key::E)) c = 'e';
	else if (KeyPress(Key::F)) c = 'f';
	else if (KeyPress(Key::G)) c = 'g';
	else if (KeyPress(Key::H)) c = 'h';
	else if (KeyPress(Key::I)) c = 'i';
	else if (KeyPress(Key::J)) c = 'j';
	else if (KeyPress(Key::K)) c = 'k';
	else if (KeyPress(Key::L)) c = 'l';
	else if (KeyPress(Key::M)) c = 'm';
	else if (KeyPress(Key::N)) c = 'n';
	else if (KeyPress(Key::O)) c = 'o';
	else if (KeyPress(Key::P)) c = 'p';
	else if (KeyPress(Key::Q)) c = 'q';
	else if (KeyPress(Key::R)) c = 'r';
	else if (KeyPress(Key::S)) c = 's';
	else if (KeyPress(Key::T)) c = 't';
	else if (KeyPress(Key::U)) c = 'u';
	else if (KeyPress(Key::V)) c = 'v';
	else if (KeyPress(Key::W)) c = 'w';
	else if (KeyPress(Key::X)) c = 'x';
	else if (KeyPress(Key::Y)) c = 'y';
	else if (KeyPress(Key::Z)) c = 'z';

	if (c != 0 && (KeyHold(Key::LShift) || KeyHold(Key::RShift)))
	{
		c -= 32;
	}
	if (KeyPress(Key::Space)) c = ' ';

	if (c != 0) out_str.push_back(c);
}
