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

xe::Event xe::InputSystem::KeyEvent(const Key key)
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
			return Pressed;
		}
	}
	else if (keyFound)
	{
		keyHold.erase(keyHold.begin() + index);
		return Released;
	}

	return None;
}

void xe::InputSystem::Typing(std::string& out_str)
{
	if (KeyEvent(Key::Backspace) == Pressed && out_str.size() > 0)
	{
		out_str.pop_back();
		return;
	}

	if (KeyEvent(Key::Enter) == Pressed)
	{
		out_str.push_back('\n');
		return;
	}

	char c = 0;
	if (KeyEvent(Key::A) == Pressed) c = 'a';
	else if (KeyEvent(Key::B) == Pressed) c = 'b';
	else if (KeyEvent(Key::C) == Pressed) c = 'c';
	else if (KeyEvent(Key::D) == Pressed) c = 'd';
	else if (KeyEvent(Key::E) == Pressed) c = 'e';
	else if (KeyEvent(Key::F) == Pressed) c = 'f';
	else if (KeyEvent(Key::G) == Pressed) c = 'g';
	else if (KeyEvent(Key::H) == Pressed) c = 'h';
	else if (KeyEvent(Key::I) == Pressed) c = 'i';
	else if (KeyEvent(Key::J) == Pressed) c = 'j';
	else if (KeyEvent(Key::K) == Pressed) c = 'k';
	else if (KeyEvent(Key::L) == Pressed) c = 'l';
	else if (KeyEvent(Key::M) == Pressed) c = 'm';
	else if (KeyEvent(Key::N) == Pressed) c = 'n';
	else if (KeyEvent(Key::O) == Pressed) c = 'o';
	else if (KeyEvent(Key::P) == Pressed) c = 'p';
	else if (KeyEvent(Key::Q) == Pressed) c = 'q';
	else if (KeyEvent(Key::R) == Pressed) c = 'r';
	else if (KeyEvent(Key::S) == Pressed) c = 's';
	else if (KeyEvent(Key::T) == Pressed) c = 't';
	else if (KeyEvent(Key::U) == Pressed) c = 'u';
	else if (KeyEvent(Key::V) == Pressed) c = 'v';
	else if (KeyEvent(Key::W) == Pressed) c = 'w';
	else if (KeyEvent(Key::X) == Pressed) c = 'x';
	else if (KeyEvent(Key::Y) == Pressed) c = 'y';
	else if (KeyEvent(Key::Z) == Pressed) c = 'z';

	if (c != 0 && (KeyHold(Key::LShift) || KeyHold(Key::RShift)))
	{
		c -= 32;
	}
	if (KeyEvent(Key::Space) == Pressed) c = ' ';

	if (c != 0) out_str.push_back(c);
	//TODO add Numbers and Symbols
}
