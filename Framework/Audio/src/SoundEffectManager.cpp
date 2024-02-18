#include "Pch.h"
#include "SoundEffectManager.h"

#include "AudioSystem.h"

namespace dx = DirectX;

namespace
{
	std::unique_ptr<xe::Audio::SoundEffectManager> s_soundEffectManager;
}

void xe::Audio::SoundEffectManager::Initialize(const std::filesystem::path root)
{
	ASSERT(s_soundEffectManager == nullptr, "SoundEffectManager -> is already initialized");
	s_soundEffectManager = std::make_unique<SoundEffectManager>();
	s_soundEffectManager->m_root = root;
}

void xe::Audio::SoundEffectManager::Terminate()
{
	if (s_soundEffectManager != nullptr)
	{
		Clear();
		s_soundEffectManager.reset();
	}
}

void xe::Audio::SoundEffectManager::SetRootPath(const std::filesystem::path& root)
{
	s_soundEffectManager->m_root = root;
}

xe::Audio::SoundID xe::Audio::SoundEffectManager::Load(const std::filesystem::path& filename)
{
	std::filesystem::path fullpath = s_soundEffectManager->m_root / filename;
	size_t soundID = std::filesystem::hash_value(fullpath);
	auto [iter, success] = s_soundEffectManager->m_inventory.insert({ soundID, nullptr });
	if (success)
	{
		auto& soundEventPtr = iter->second;
		soundEventPtr = std::make_unique<Entry>();
		soundEventPtr->effect = std::make_unique<dx::SoundEffect>(AudioSystem::GetAudioEngine(), fullpath.wstring().c_str());
		soundEventPtr->instance = soundEventPtr->effect->CreateInstance();
	}
	return soundID;
}

void xe::Audio::SoundEffectManager::Clear()
{
	AudioSystem::Suspend();

	for (auto& entryPair : s_soundEffectManager->m_inventory)
	{
		if (entryPair.second)
		{
			entryPair.second->instance->Stop();
			entryPair.second->instance.reset();
			entryPair.second->effect.reset();
		}
	}
	s_soundEffectManager->m_inventory.clear();
}

void xe::Audio::SoundEffectManager::Play(SoundID id, bool doLoop)
{
	auto iter = s_soundEffectManager->m_inventory.find(id);
	if (iter != s_soundEffectManager->m_inventory.end())
	{
		iter->second->instance->Play(doLoop);
	}
}

void xe::Audio::SoundEffectManager::Stop(SoundID id)
{
	auto iter = s_soundEffectManager->m_inventory.find(id);
	if (iter != s_soundEffectManager->m_inventory.end())
	{
		iter->second->instance->Stop();
	}
}
