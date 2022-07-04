#pragma once
#include "Libraries.h"

namespace xe
{
	class Timer
	{
		sf::Clock clock{};

	public:
		float GetElapsed() const;
		void Reset();
		sf::Clock& UnPack();
	};
}

