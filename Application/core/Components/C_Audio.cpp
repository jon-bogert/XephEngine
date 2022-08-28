#include "C_Audio.h"
namespace C
{
	Audio::Audio(std::string name, GameObject* gameObject)
		:Component(gameObject)
		, audioName(name)
	{
	}
	Audio::Audio(GameObject* gameObject)
		:Component(gameObject)
	{
	}
		
	void Audio::Start()
	{
		LoadAudio(audioName);
	}
	
	void Audio::Update()
	{
		
	}
	void Audio::LoadAudio(const std::string name)
	{
		UnloadAudio();
		audioName = name;

		if (Engine::GetActiveScene()->FindAudioSource(name) != nullptr)
		{
			source = new sf::Sound;
			source->setBuffer(*Engine::GetActiveScene()->FindAudioSource(name)->UnWrap());
		}
		else if (Engine::GetActiveScene()->FindAudioStream(name) != nullptr)
		{
			stream = Engine::GetActiveScene()->FindAudioStream(name);
			isStream = true;
		}

	}
	void Audio::UnloadAudio()
	{
		audioName = "";
		delete source;
		source = nullptr;
		stream = nullptr;
		isStream = false;
	}
	void Audio::Play()
	{
		if (!isStream)
		{
			source->play();
		}
		else
		{
			stream->Play();
		}
	}
	void Audio::Pause()
	{
		if (!isStream)
		{
			source->pause();
		}
		else
		{
			stream->Pause();
		}
	}
	void Audio::Stop()
	{
		if (!isStream)
		{
			source->stop();
		}
		else
		{
			stream->Stop();
		}
	}
	void Audio::SetLooping(const bool setTo)
	{
		if (!isStream)
		{
			source->setLoop(setTo);
		}
		else
		{
			stream->SetLooping(setTo);
		}
	}
	bool Audio::GetIsLooping() const
	{
		if (!isStream)
		{
			return source->getLoop();
		}
		return stream->GetIsLooping();
	}
	float Audio::GetDuration() const
	{
		if (!isStream)
		{
			return Engine::GetActiveScene()->FindAudioSource(audioName)->GetDuration();
		}
		return stream->GetDuration();
	}
	float Audio::GetLoopStart() const
	{
		if (!isStream)
		{
			Debug::LogWarn("Cannot set loop points on and AudioSource. Switch to AudioStream");
			return 0.0f;
		}
		return stream->GetLoopStart();
	}
	float Audio::GetLoopEnd() const
	{
		if (!isStream)
		{
			Debug::LogWarn("Cannot set loop points on and AudioSource. Switch to AudioStream");
			return 0.0f;
		}
		return stream->GetLoopEnd();
	}
	float Audio::GetLoopLength() const
	{
		if (!isStream)
		{
			Debug::LogWarn("Cannot set loop points on and AudioSource. Switch to AudioStream");
			return 0.0f;
		}
		return stream->GetLoopLength();
	}
	void Audio::SetLoopPoints(float start, float end)
	{
		if (!isStream)
		{
			Debug::LogWarn("Cannot set loop points on and AudioSource. Switch to AudioStream");
			return;
		}
		stream->SetLoopPoints(start, end);
	}
	void Audio::SetLoopLength(float start, float length)
	{
		if (!isStream)
		{
			Debug::LogWarn("Cannot set loop points on and AudioSource. Switch to AudioStream");
			return;
		}
		stream->SetLoopLength(start, length);
	}
	float Audio::GetVolume() const
	{
		if (!isStream)
		{
			return source->getVolume() * 0.01f;
		}
		return stream->GetVolume();
	}
	void Audio::SetVolume(float volume)
	{
		if (!isStream)
		{
			source->setVolume((int)(volume * 100));
		}
		else
		{
			stream->SetVolume(volume);
		}
	}
	float Audio::GetPlayPosition()
	{
		if (!isStream)
		{
			return source->getPlayingOffset().asSeconds();
		}
		return stream->GetPlayPosition();
	}
	void Audio::SetPlayPosition(const float newPosition)
	{
		if (!isStream)
		{
			source->setPlayingOffset(sf::seconds(newPosition));
		}
		else
		{
			stream->SetPlayPosition(newPosition);
		}
	}
	bool Audio::GetIsPlaying() const
	{
		if (!isStream)
		{
			return (source->getStatus() == sf::Music::Playing);
		}
		return stream->GetIsPlaying();
	}
}
