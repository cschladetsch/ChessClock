#include "Gambit/Exceptions.hpp"
#include "Gambit/AudioAtlas.hpp"
#include "Gambit/ThirdParty/SDL.hpp"

namespace Gambit
{
    AudioAtlas::AudioAtlas(ResourceId const &id, const char *fileName)
    {
    //    : ResourceBase(id)
    //    , JsonReader(fileName)
    //{
    //    auto defaultDriver = SDL_GetCurrentAudioDriver();
    //    int result = SDL_AudioInit(defaultDriver);
    //    if (result != 0)
    //    {
    //        LOG_ERROR() << "Failed to init audio driver " << defaultDriver << "\n";
    //        return;
    //    }
    }

    void AudioAtlas::SetVolume(float zeroToOne)
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    void AudioAtlas::SetVolume(string clip, float zeroToOne)
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    bool AudioAtlas::Play(string name)
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    void AudioAtlas::Stop(string name)
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    void AudioAtlas::Stop()
    {
        GAMBIT_NOT_IMPLEMENTED();
    }

    bool AudioAtlas::ParseJson(JsonNext &next)
    {
        return true;// GAMBIT_NOT_IMPLEMENTED();
    }
}
