#include "Gambit/AudioClip.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    SDL_AudioCVT AudioClip::null_cvt;

    AudioClip::AudioClip(ResourceId const &id, const char *file)
        : ResourceBase(id)
    {
        int index{ 0 };
        SDL_AudioSpec wave;
        Uint8 *data{ 0 };
        Uint32 dlen{ 0 };
        if (SDL_LoadWAV(file, &wave, &data, &dlen) == NULL)
        {
            LOG_ERROR() << "Couldn't load " << file << " as .wav file";
            return;
        }
        SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq, AUDIO_S16, 2, 22050);
        cvt.buf = (uint8_t *)malloc(dlen * cvt.len_mult);
        if (cvt.buf == 0)
        {
            LOG_ERROR() << "Couldn't load " << file << " as .wav file";
            return;
        }

        memcpy(cvt.buf, data, dlen);
        cvt.len = dlen;
        SDL_ConvertAudio(&cvt);
        SDL_FreeWAV(data);
    }

    void AudioClip::DeleteRaw(uint8_t *ptr)
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
