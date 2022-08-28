#include "AudioSource.h"
#include "../systems/Debug.h"

xe::AudioSource::AudioSource(std::string path)
{
	source = new sf::SoundBuffer;
	if (!source->loadFromFile(path))
	{
		delete source;
		source = nullptr;
		xe::Debug::LogErr("Failed to load AudioSource from %s.", path.c_str());
		return;
	}
}

xe::AudioSource::~AudioSource()
{
	delete source;
}

sf::SoundBuffer* xe::AudioSource::UnWrap()
{
	return source;
}

float xe::AudioSource::GetDuration() const
{
	return source->getDuration().asSeconds();
}
