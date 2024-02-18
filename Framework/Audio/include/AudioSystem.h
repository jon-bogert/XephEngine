#ifndef __XE_AUDIO_AUDIOSYSTEM_H__
#define __XE_AUDIO_AUDIOSYSTEM_H__

namespace xe::Audio
{
    class AudioSystem final
    {
    public:
        AudioSystem() = default;
        ~AudioSystem() = default;
        AudioSystem(const AudioSystem& other) = delete;
        AudioSystem(const AudioSystem&& other) = delete;
        AudioSystem operator=(const AudioSystem& other) = delete;
        AudioSystem operator=(const AudioSystem&& other) = delete;

        static void Initialize();
        static void Terminate();

        static void Update();
        static void Suspend();

        static DirectX::AudioEngine* GetAudioEngine();

    private:

        void _Initialize();
        void _Terminate();

        DirectX::AudioEngine* m_audioEngine = nullptr;
    };

}

#endif //!__XE_AUDIO_AUDIOSYSTEM_H__