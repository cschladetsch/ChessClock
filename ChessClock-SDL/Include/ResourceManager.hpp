#pragma once

#include <memory>

#include "ChessClock/Texture.hpp"
#include "ChessClock/Sprite.hpp"
#include "ChessClock/Font.hpp"

namespace ChessClock
{
    class ResourceManager
    {
        std::string  _rootDir;

    public:
        ResourceManager(const char* root);

        std::shared_ptr<Texture> GetTexture(const char* name);
        std::shared_ptr<Sprite> GetSprite(const char* name);
        std::shared_ptr<Font> GetFont(const char* name);
    };
}
