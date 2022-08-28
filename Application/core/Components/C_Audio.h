#pragma once
#include "XephEngine/Engine.h"
#include "src/Resources.h"

using namespace xe;

namespace C
{
	class Audio : public Component
	{
	protected:
		bool isStream{};
		sf::Sound* source = nullptr;
		AudioStream* stream = nullptr;
		std::string audioName{};
	
	public:
		Audio(std::string name, GameObject* gameObject);
		Audio(GameObject* gameObject);
		
		void Start();
		void Update();

		void LoadAudio(const std::string name);
		void UnloadAudio();

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

