#include "Gambit/Exceptions.hpp"
#include "Gambit/AudioAtlas.hpp"

namespace Gambit
{
    AudioAtlas::AudioAtlas(ResourceId const &id, const char *fileName)
        : ResourceBase(id)
    {
        if (!ReadJson(fileName))
        {
            LOG_ERROR() << "Couldn't read " << fileName << "\n";
        }
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
        GAMBIT_NOT_IMPLEMENTED();
    }
}
