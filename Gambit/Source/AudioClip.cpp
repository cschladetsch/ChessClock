#include "Gambit/AudioClip.hpp"

namespace Gambit
{
    AudioClip::AudioClip(ResourceId const &id, const char *file)
        : ResourceBase(id)
    {
    }

    void AudioClip::Deleter(AudioClip *)
    {
    }

    void AudioClip::Play()
    {
    }

    void AudioClip::SetVolume(float zeroToOne)
    {
    }

    void AudioClip::Stop()
    {
    }
}
