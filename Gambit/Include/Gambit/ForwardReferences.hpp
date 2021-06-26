#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>

#include "Gambit/Config.hpp"
#include "Gambit/NonCopyable.hpp"

extern "C"
{
    struct _TTF_Font;
    struct SDL_Texture;
    struct SDL_Surface;
    struct SDL_Color;
    struct SDL_Renderer;
    struct SDL_Window;
    struct SDL_Rect;
    uint32_t SDL_GetTicks();
}

namespace Gambit
{
    struct Vector2;
    class ResourceManager;
    class ResourceBase;
    class Renderer;

    class Font;
    class TimerFont;
    class Texture;
    class Button;
    class Object;
    class TextEntry;
    class Sprite;
    class Atlas;
    class Scene;
    class AudioClip;
    struct Color;

    typedef shared_ptr<Scene> AudioClipPtr;
    typedef shared_ptr<Scene> ScenePtr;
    typedef shared_ptr<Atlas> AtlasPtr;
    typedef shared_ptr<Sprite> SpritePtr;
    typedef shared_ptr<TextEntry> TextEntryPtr;
    typedef shared_ptr<Button> ButtonPtr;
    typedef shared_ptr<Font> FontPtr;
    typedef shared_ptr<TimerFont> NumberFontPtr;
    typedef shared_ptr<Texture> TexturePtr;
    typedef shared_ptr<Object> ObjectPtr;
    typedef shared_ptr<ResourceBase> ResourceBasePtr;
}

namespace std
{
    template <class _Elem, class _Traits>
    class basic_fstream;

    using fstream = basic_fstream<char, char_traits<char>>;
}

