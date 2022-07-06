#include "InputSystem.h"
#include <windows.h>
#include <xinput.h>

sf::Event inputEvent;

std::vector<xe::Key> keyHold;
std::vector<std::pair<int, xe::Button>> buttonHold;
std::vector<std::pair<std::string, xe::Vector2>> keyAxis2DBuffer;
std::vector<std::pair<std::string, float >> keyAxis1DBuffer;
float axisThrow = 15.f;

struct XE_CONTROLLER_TRIG { float LT = 0.f; float RT = 0.f; };
float deadZoneMin = 0.3f;
float deadZoneMax = 1.f;

XE_CONTROLLER_TRIG GetTriggerPosition(int playrIndex)
{
	XINPUT_STATE state{};
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	XInputGetState(0, &state);
	return { (float)state.Gamepad.bLeftTrigger / 255, (float)state.Gamepad.bRightTrigger / 255 };
}

float DeadZone(const float input)
{
	if (fabs(input) < deadZoneMin)
	{
		return 0.f;
	}
	else if (fabs(input) > deadZoneMax)
	{
		if (input >= 0.f) { return 1.f; }
		else { return -1.f; }
	}
	else
	{
		if (input >= 0.f)
		{
			return (input - deadZoneMin) * (1 / (deadZoneMax - deadZoneMin));
		}
		else
		{
			return (input + deadZoneMin) * (1 / (deadZoneMax - deadZoneMin));
		}
	}
}

bool xe::InputSystem::Update()
{
	return Engine::GetWindow()->UnWrap()->pollEvent(inputEvent);
}

bool xe::InputSystem::CloseWindow()
{
	return (inputEvent.type == sf::Event::Closed);
}

float xe::InputSystem::KeyAxis1D(const Key pos, const Key neg)
{
	float target{};
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)pos));
	axisId.append(std::to_string((int)neg));

	//Find initial direcrions
	if (KeyHold(pos) && !KeyHold(neg))
		target = 1;
	else if (!KeyHold(pos) && KeyHold(neg))
		target = -1;

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, float> entry : keyAxis1DBuffer)
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target == 0 && keyAxis1DBuffer[index].second == 0)
	{
		keyAxis1DBuffer.erase(keyAxis1DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = axisThrow * Time::DeltaTime();
		//Create buffer if doesn't exist
		if (!inBuffer)
			keyAxis1DBuffer.push_back({ axisId, 0.f });

		//Apply Throw
		if ((keyAxis1DBuffer[index].second < target) && (keyAxis1DBuffer[index].second + axisThrowDT < target))
		{
			keyAxis1DBuffer[index].second += axisThrowDT;
		}
		else if ((keyAxis1DBuffer[index].second > target) && (keyAxis1DBuffer[index].second - axisThrowDT > target))
		{
			keyAxis1DBuffer[index].second -= axisThrowDT;
		}
		else if (((keyAxis1DBuffer[index].second < target) && (keyAxis1DBuffer[index].second + axisThrowDT >= target))
			|| ((keyAxis1DBuffer[index].second > target) && (keyAxis1DBuffer[index].second - axisThrowDT <= target)))
		{
			keyAxis1DBuffer[index].second = target;
		}

		return keyAxis1DBuffer[index].second;
	}

	return 0.f;
}

xe::Vector2 xe::InputSystem::KeyAxis2D(const Key posX, const Key negX, const Key posY, const Key negY)
{
	Vector2 target{};
	std::string axisId{};
	//get AxisID
	axisId.append(std::to_string((int)posX));
	axisId.append(std::to_string((int)negX));
	axisId.append(std::to_string((int)posY));
	axisId.append(std::to_string((int)negY));

	//Find initial direcrions
	if (KeyHold(posX) && !KeyHold(negX))
		target.x = 1;
	else if (!KeyHold(posX) && KeyHold(negX))
		target.x = -1;

	if (KeyHold(posY) && !KeyHold(negY))
		target.y = 1;
	else if (!KeyHold(posY) && KeyHold(negY))
		target.y = -1;

	if (target.x != 0 && target.y != 0)
	{
		target.x = sqrtf(0.5f)* target.x;
		target.y = sqrtf(0.5f)* target.y;
	}

	//check exist in buffer
	bool inBuffer{};
	int index{};

	for (std::pair<std::string, Vector2> entry : keyAxis2DBuffer)
	{
		if (entry.first == axisId)
		{
			inBuffer = true;
			break;
		}
		else index++;
	}

	//Check to destroy
	if (inBuffer && target.x == 0 && target.y == 0
		&& keyAxis2DBuffer[index].second.x == 0
		&& keyAxis2DBuffer[index].second.y == 0)
	{
		keyAxis2DBuffer.erase(keyAxis2DBuffer.begin() + index);
	}
	//Buffer needs to exist
	else
	{
		float axisThrowDT = axisThrow * Time::DeltaTime();
		//Create buffer if doesn't exist
		if (!inBuffer)
			keyAxis2DBuffer.push_back({ axisId, Vector2() });

		//Apply Throw
		if ((keyAxis2DBuffer[index].second.x < target.x) && (keyAxis2DBuffer[index].second.x + axisThrowDT < target.x))
		{
			keyAxis2DBuffer[index].second.x += axisThrowDT;
		}
		else if ((keyAxis2DBuffer[index].second.x > target.x) && (keyAxis2DBuffer[index].second.x - axisThrowDT > target.x))
		{
			keyAxis2DBuffer[index].second.x -= axisThrowDT;
		}
		else if (((keyAxis2DBuffer[index].second.x < target.x) && (keyAxis2DBuffer[index].second.x + axisThrowDT >= target.x))
			|| ((keyAxis2DBuffer[index].second.x > target.x) && (keyAxis2DBuffer[index].second.x - axisThrowDT <= target.x)))
		{
			keyAxis2DBuffer[index].second.x = target.x;
		}

		if ((keyAxis2DBuffer[index].second.y < target.y) && (keyAxis2DBuffer[index].second.y + axisThrowDT < target.y))
		{
			keyAxis2DBuffer[index].second.y += axisThrowDT;
		}
		else if ((keyAxis2DBuffer[index].second.y > target.y) && (keyAxis2DBuffer[index].second.y - axisThrowDT > target.y))
		{
			keyAxis2DBuffer[index].second.y -= axisThrowDT;
		}
		else if (((keyAxis2DBuffer[index].second.y < target.y) && (keyAxis2DBuffer[index].second.y + axisThrowDT >= target.y))
			|| ((keyAxis2DBuffer[index].second.y > target.y) && (keyAxis2DBuffer[index].second.y - axisThrowDT <= target.y)))
		{
			keyAxis2DBuffer[index].second.y = target.y;
		}

		return keyAxis2DBuffer[index].second;
	}

	return Vector2();
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

xe::Vector2 xe::InputSystem::GetAxis(int playerIndex, Axis axis)
{
	Vector2 result{};

	switch (axis)
	{
	case Axis::LS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::X) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::Y) / -100.f);
		break;
	case Axis::RS:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::U) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::V) / -100.f);
		break;
	case Axis::DPad:
		result.x = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovX) / 100.f);
		result.y = DeadZone(sf::Joystick::getAxisPosition(playerIndex, sf::Joystick::PovY) / 100.f);
		break;
	case Axis::Trig:
		result = { GetTriggerPosition(playerIndex).LT, GetTriggerPosition(playerIndex).RT };
		break;
	}

	return result;
}

bool xe::InputSystem::ButtonHold(const int playerIndex, const Button button)
{
	if (button <= Button::RS_Press)
	{
		return sf::Joystick::isButtonPressed(playerIndex, (int)button);
	}

	switch (button)
	{
	case Button::LT:
		return (GetAxis(playerIndex, Axis::Trig).x > 0);
		break;
	case Button::RT:
		return (GetAxis(playerIndex, Axis::Trig).y > 0);
		break;

	case Button::LS_Up:
		return (GetAxis(playerIndex, Axis::LS).y > 0);
		break;
	case Button::LS_Down:
		return (GetAxis(playerIndex, Axis::LS).y < 0);
		break;
	case Button::LS_Left:
		return (GetAxis(playerIndex, Axis::LS).x < 0);
		break;
	case Button::LS_Right:
		return (GetAxis(playerIndex, Axis::LS).x > 0);
		break;

	case Button::RS_Up:
		return (GetAxis(playerIndex, Axis::RS).y > 0);
		break;
	case Button::RS_Down:
		return (GetAxis(playerIndex, Axis::RS).y < 0);
		break;
	case Button::RS_Left:
		return (GetAxis(playerIndex, Axis::RS).x < 0);
		break;
	case Button::RS_Right:
		return (GetAxis(playerIndex, Axis::RS).x > 0);
		break;

	case Button::DPad_Up:
		return (GetAxis(playerIndex, Axis::DPad).y > 0);
		break;
	case Button::DPad_Down:
		return (GetAxis(playerIndex, Axis::DPad).y < 0);
		break;
	case Button::DPad_Left:
		return (GetAxis(playerIndex, Axis::DPad).x < 0);
		break;
	case Button::DPad_Right:
		return (GetAxis(playerIndex, Axis::DPad).x > 0);
		break;
	}
	return false;
}

xe::Event xe::InputSystem::ButtonEvent(const int playerIndex, const Button button)
{
	bool buttonFound{};
	int index{};
	for (std::pair<int, Button> b : buttonHold)
	{
		if (b.first == playerIndex && b.second == button)
		{
			buttonFound = true;
			break;
		}
		else index++;
	}

	if (ButtonHold(playerIndex, button))
	{
		if (!buttonFound)
		{
			buttonHold.push_back({ playerIndex, button });
			return Pressed;
		}
	}
	else if (buttonFound)
	{
		buttonHold.erase(buttonHold.begin() + index);
		return Released;
	}

	return None;
}

void xe::InputSystem::TestFunction()
{
	if (ButtonEvent(0, Button::LT) == Released) std::cout << "LT" << std::endl;
	if (ButtonEvent(0, Button::RT) == Released) std::cout << "RT" << std::endl;
	if (ButtonEvent(0, Button::LS_Up) == Released) std::cout << "LUp" << std::endl;
	if (ButtonEvent(0, Button::LS_Down) == Released) std::cout << "LDown" << std::endl;
	if (ButtonEvent(0, Button::LS_Left) == Released) std::cout << "LLeft" << std::endl;
	if (ButtonEvent(0, Button::LS_Right) == Released) std::cout << "LRight" << std::endl;
	if (ButtonEvent(0, Button::RS_Up) == Released) std::cout << "RUp" << std::endl;
	if (ButtonEvent(0, Button::RS_Down) == Released) std::cout << "RDown" << std::endl;
	if (ButtonEvent(0, Button::RS_Left) == Released) std::cout << "RLeft" << std::endl;
	if (ButtonEvent(0, Button::RS_Right) == Released) std::cout << "RRight" << std::endl;
	if (ButtonEvent(0, Button::DPad_Up) == Released) std::cout << "DUp" << std::endl;
	if (ButtonEvent(0, Button::DPad_Down) == Released) std::cout << "DDown" << std::endl;
	if (ButtonEvent(0, Button::DPad_Left) == Released) std::cout << "DLeft" << std::endl;
	if (ButtonEvent(0, Button::DPad_Right) == Released) std::cout << "DRight" << std::endl;
	if (ButtonEvent(0, Button::A) == Released) std::cout << "A" << std::endl;

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
