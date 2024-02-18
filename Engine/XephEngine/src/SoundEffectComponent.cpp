#include "Pch.h"
#include "SoundEffectComponent.h"
#include "GameObject.h"


using namespace xe::Audio;

void xe::SoundEffectComponent::Initialize()
{
	ASSERT(!m_filename.empty(), "SoundEffectComponent: no sound file loaded");
	m_soundID = SoundEffectManager::Load(m_filename);
}

void xe::SoundEffectComponent::Terminate()
{

}

void xe::SoundEffectComponent::Deserialize(const yaml_val& data)
{
	m_filename = data["filename"].as<std::string>();
	m_doLoop = data["loop"].as<bool>();
}

void xe::SoundEffectComponent::DebugUI()
{
	std::string buttonName = GetGameObject().GetName();
	if (ImGui::Button(("Play##play" + buttonName).c_str()))
	{
		Play();
	}
}

void xe::SoundEffectComponent::Play()
{
	Stop();
	SoundEffectManager::Play(m_soundID, m_doLoop);
}

void xe::SoundEffectComponent::Stop()
{
	SoundEffectManager::Stop(m_soundID);
}
