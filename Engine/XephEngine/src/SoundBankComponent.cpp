#include "Pch.h"
#include "SoundBankComponent.h"

#include "GameObject.h"


using namespace xe::Audio;

void xe::SoundBankComponent::Initialize()
{
	for (auto& soundPair : m_soundEffects)
	{
		soundPair.second.soundID = SoundEffectManager::Load(soundPair.second.filename);
	}
}

void xe::SoundBankComponent::Terminate()
{

}

void xe::SoundBankComponent::Deserialize(const yaml_val& data)
{
	for (yaml_val sound : data["sounds"])
	{
		std::string key = sound["key"].as<std::string>();
		SoundData& soundData = m_soundEffects[key];
		soundData.filename = sound["filename"].as<std::string>();
		soundData.doLoop = sound["loop"].as<bool>();
	}
}

void xe::SoundBankComponent::DebugUI()
{
	std::string buttonName = GetGameObject().GetName();
	for (auto& soundPair : m_soundEffects)
	{
		if (ImGui::Button(("Play " + soundPair.first).c_str()))
		{
			Play(soundPair.first);
		}
	}
}

void xe::SoundBankComponent::Play(const std::string& key)
{
	if (m_soundEffects.find(key) == m_soundEffects.end())
		return;

	Stop(key);
	SoundEffectManager::Play(m_soundEffects[key].soundID, m_soundEffects[key].doLoop);
}

void xe::SoundBankComponent::Stop(const std::string& key)
{
	if (m_soundEffects.find(key) == m_soundEffects.end())
		return;

	SoundEffectManager::Stop(m_soundEffects[key].soundID);
}

void xe::SoundBankComponent::StopAll()
{
	for (auto& soundPair : m_soundEffects)
	{
		Stop(soundPair.first);
	}
}
