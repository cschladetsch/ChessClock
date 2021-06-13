#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/Resource.hpp"

namespace Gambit
{
    class AudioClip
        : public ResourceBase
    {
        static inline Logger _log{ "AudioClip" };

    public:
        AudioClip(ResourceId const &id, const char *file);

        void Deleter(AudioClip *);

        void Play();
        void SetVolume(float zeroToOne);
        void Stop();
    };
}
