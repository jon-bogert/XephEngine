#pragma once
#include "../Libraries.h"

namespace xe
{
	class AudioSource
	{
		sf::SoundBuffer* source = nullptr;

	public:
		AudioSource(std::string path);
		~AudioSource();

		sf::SoundBuffer* UnWrap();
		float GetDuration() const;
	};
}

