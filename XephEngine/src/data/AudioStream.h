#pragma once
#include "../Libraries.h"

namespace xe
{
	class AudioStream
	{
		sf::Music* source = nullptr;

	public:
		AudioStream(std::string path);
		~AudioStream();

		sf::Music* UnWrap();

		void Play();
		void Pause();
		void Stop();

		void SetLooping(const bool setTo);
		bool GetIsLooping() const;

		float GetDuration() const;

		float GetLoopStart() const;
		float GetLoopEnd() const;
		float GetLoopLength() const;
		void SetLoopPoints(float start, float end);
		void SetLoopLength(float start, float length);

		float GetVolume() const;
		void SetVolume(float volume);

		float GetPlayPosition();
		void SetPlayPosition(const float newPosition);

		bool GetIsPlaying() const;
	};
}

