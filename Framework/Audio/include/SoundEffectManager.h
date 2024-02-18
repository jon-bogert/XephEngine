#ifndef __XE_AUDIO_SOUNDEFFECTMANAGER_H__
#define __XE_AUDIO_SOUNDEFFECTMANAGER_H__

namespace xe::Audio
{
	using SoundID = size_t;

	class SoundEffectManager final
	{
	public:
		static void Initialize(const std::filesystem::path root);
		static void Terminate();

		SoundEffectManager() = default;
		SoundEffectManager(const SoundEffectManager&) = delete;
		SoundEffectManager(const SoundEffectManager&&) = delete;
		SoundEffectManager& operator=(const SoundEffectManager&) = delete;
		SoundEffectManager& operator=(const SoundEffectManager&&) = delete;

		static void SetRootPath(const std::filesystem::path& root);

		static SoundID Load(const std::filesystem::path& filename);
		static void Clear();
		
		static void Play(SoundID id, bool doLoop = false);
		static void Stop(SoundID id);

	private:
		struct Entry
		{
			std::unique_ptr<DirectX::SoundEffect> effect;
			std::unique_ptr<DirectX::SoundEffectInstance> instance;
		};

		using SoundEffects = std::unordered_map<SoundID, std::unique_ptr<Entry>>;
		SoundEffects m_inventory;

		std::filesystem::path m_root;
	};
}

#endif //!__XE_AUDIO_SOUNDEFFECTMANAGER_H__
