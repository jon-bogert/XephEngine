#ifndef __XE_XEPHENGINE_SOUNDEFFECTCOMPONENT_H__
#define __XE_XEPHENGINE_SOUNDEFFECTCOMPONENT_H__

#include "Component.h"

namespace xe
{
	class SoundEffectComponent final : public Component
	{
	public:
		SET_TYPE_ID(ComponentID::SoundEffect);

		void Initialize() override;
		void Terminate() override;
		void Deserialize(const yaml_val& data) override;

		void DebugUI() override;

		void Play();
		void Stop();

	private:
		std::string m_filename;
		Audio::SoundID m_soundID;
		bool m_doLoop = false;
	};
}

#endif //!__XE_XEPHENGINE_SOUNDEFFECTCOMPONENT_H__