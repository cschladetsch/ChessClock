#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <functional>

#include "Gambit/Config.hpp"

extern "C"
{
    struct _TTF_Font;
    struct SDL_Texture;
    struct SDL_Surface;
    struct SDL_Color;
    struct SDL_Renderer;
    struct SDL_Window;
    struct SDL_Rect;
}

namespace Gambit
{
    struct Vector2;
    class ResourceManager;
    class ResourceBase;
    class Renderer;

    class Transform;
    class Font;
    class TimerFont;
    class Texture;
    class Button;
    class Object;
    class TextEntry;
    class Sprite;

    typedef shared_ptr<Sprite> SpritePtr;
    typedef shared_ptr<TextEntry> TextEntryPtr;
    typedef shared_ptr<Button> ButtonPtr;
    typedef shared_ptr<Font> FontPtr;
    typedef shared_ptr<TimerFont> NumberFontPtr;
    typedef shared_ptr<Texture> TexturePtr;
    typedef shared_ptr<Object> ObjectPtr;
    typedef shared_ptr<ResourceBase> ResourceBasePtr;
    typedef shared_ptr<Transform> TransformPtr;
}

