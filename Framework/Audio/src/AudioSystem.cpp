#include "Pch.h"
#include "AudioSystem.h"


using namespace DirectX;

namespace
{
	std::unique_ptr<xe::Audio::AudioSystem> s_audioSystem;
}

void xe::Audio::AudioSystem::Initialize()
{
	ASSERT(s_audioSystem == nullptr, "AudioSystem has already been initialized");
	s_audioSystem = std::make_unique<AudioSystem>();
	s_audioSystem->_Initialize();
}

void xe::Audio::AudioSystem::Terminate()
{
	if (s_audioSystem != nullptr)
	{
		s_audioSystem->_Terminate();
		s_audioSystem.reset();
	}
}

void xe::Audio::AudioSystem::Update()
{
	if (s_audioSystem->m_audioEngine != nullptr && s_audioSystem->m_audioEngine->Update())
	{
		if (s_audioSystem->m_audioEngine->IsCriticalError())
		{
			LOG("AudioSystem -> critical error, shutting down");
			Terminate();
		}
	}
}

void xe::Audio::AudioSystem::Suspend()
{
	ASSERT(s_audioSystem->m_audioEngine != nullptr, "AudioSystem -> audio engine is not available");
	s_audioSystem->m_audioEngine->Suspend();
}

DirectX::AudioEngine* xe::Audio::AudioSystem::GetAudioEngine()
{
	return s_audioSystem->m_audioEngine;
}

void xe::Audio::AudioSystem::_Initialize()
{
	ASSERT(m_audioEngine == nullptr, "AudioSystem-> is already initialized");
	AUDIO_ENGINE_FLAGS flags = AudioEngine_Default;

#ifdef _DEBUG
	flags |= AudioEngine_Debug;
#endif;

	m_audioEngine = new AudioEngine(flags);
}

void xe::Audio::AudioSystem::_Terminate()
{
	if (m_audioEngine != nullptr)
	{
		delete m_audioEngine;
	}
	m_audioEngine = nullptr;
}
