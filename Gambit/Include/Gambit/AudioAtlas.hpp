#pragma once

#include <unordered_map>

#include "Gambit/Logger.hpp"
#include "Gambit/ResourceBase.hpp"
#include "Gambit/JsonReader.hpp"

namespace Gambit
{
    class AudioAtlas
        : public ResourceBase
        , JsonReader
    {
        static inline Logger _log{ "AudioAtlas" };
        typedef std::unordered_map<string, AudioClipPtr> StringToAudioClip;

        StringToAudioClip _audioClips;

    public:
        AudioAtlas(ResourceId const &id, const char *fileName);

        void SetVolume(float zeroToOne);
        void SetVolume(string clip, float zeroToOne);

        bool Play(string name);
        void Stop(string name);
        void Stop();

    private:
        bool ParseJson(JsonNext &next);
    };
}
