#pragma once

#include "Gambit/Logger.hpp"
#include "Gambit/Resource.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    class AudioClip
        : public ResourceBase
    {
        static inline Logger _log{ "AudioClip" };

        SDL_AudioCVT cvt; 

    public:
        AudioClip(ResourceId const &id, const char *file);

        void Play();
        void SetVolume(float zeroToOne);
        void Stop();

    protected:
        void DeleteRaw(uint8_t *ptr);
    };
}
