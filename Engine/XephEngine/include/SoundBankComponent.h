#ifndef __XE_XEPHENGINE_SOUNDBANKCOMPONENT_H__
#define __XE_XEPHENGINE_SOUNDBANKCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class SoundBankComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::SoundBank);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const yaml_val& data) override;

		void DebugUI() override;

		void Play(const std::string& key);
		void Stop(const std::string& key);
		void StopAll();

	private:
		struct SoundData
		{
			std::string filename;
			Audio::SoundID soundID;
			bool doLoop = false;
		};
		using SoundEffects = std::unordered_map<std::string, SoundData>;
		SoundEffects m_soundEffects;
	};
}

#endif //!__XE_XEPHENGINE_SOUNDBANKCOMPONENT_H__
