#include "Timer.h"

float xe::Timer::GetElapsed() const
{
	return clock.getElapsedTime().asSeconds();
}

void xe::Timer::Reset()
{
	clock.restart();
}

sf::Clock& xe::Timer::UnPack()
{
	return clock;
}
