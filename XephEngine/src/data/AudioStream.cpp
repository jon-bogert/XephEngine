#include "AudioStream.h"
#include "../systems/Debug.h"

xe::AudioStream::AudioStream(std::string path)
{
	source = new sf::Music;
	if (!source->openFromFile(path))
	{
		delete source;
		source = nullptr;
		xe::Debug::LogErr("Failed to open AudioStream from %s.", path.c_str());
		return;
	}
}

xe::AudioStream::~AudioStream()
{
	delete source;
}

sf::Music* xe::AudioStream::UnWrap()
{
	return source;
}

void xe::AudioStream::Play()
{
	source->play();
}

void xe::AudioStream::Pause()
{
	source->pause();
}

void xe::AudioStream::Stop()
{
	source->stop();
}

void xe::AudioStream::SetLooping(const bool setTo)
{
	source->setLoop(setTo);
}

bool xe::AudioStream::GetIsLooping() const
{
	return source->getLoop();
}

float xe::AudioStream::GetDuration() const
{
	return source->getDuration().asSeconds();
}

float xe::AudioStream::GetLoopStart() const
{
	return source->getLoopPoints().offset.asSeconds();
}

float xe::AudioStream::GetLoopEnd() const
{
	return source->getLoopPoints().offset.asSeconds() + source->getLoopPoints().length.asSeconds();
}

float xe::AudioStream::GetLoopLength() const
{
	return source->getLoopPoints().length.asSeconds();
}

void xe::AudioStream::SetLoopPoints(float start, float end)
{
	source->setLoopPoints({ sf::seconds(start), sf::seconds(end - start) });
}

void xe::AudioStream::SetLoopLength(float start, float length)
{
	source->setLoopPoints({ sf::seconds(start), sf::seconds(length) });
}

float xe::AudioStream::GetVolume() const
{
	return source->getVolume() * 0.01f;
}

void xe::AudioStream::SetVolume(float volume)
{
	source->setVolume((int)(volume * 100));
}

float xe::AudioStream::GetPlayPosition()
{
	return source->getPlayingOffset().asSeconds();
}

void xe::AudioStream::SetPlayPosition(const float newPosition)
{
	source->setPlayingOffset(sf::seconds(newPosition));
}

bool xe::AudioStream::GetIsPlaying() const
{
	return (source->getStatus() == sf::Music::Playing);
}


