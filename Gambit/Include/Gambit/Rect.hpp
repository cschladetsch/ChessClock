#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/Vector2.hpp"

namespace Gambit
{
    struct Rect
    {
        int top{ 0 }, left{ 0 }, width{ 0 }, height{ 0 };

        Rect() = default;
        Rect(int left, int top, int width, int height);
        Rect(const Rect &other)
            : top(other.top), left(other.left), width(other.width), height(other.height) { }

        Vector2 GetTopLeft() const { return Vector2(top, left); }

        bool Contains(Vector2 where) const;
    };

    inline SDL_Rect* ToSdlRect(Rect const& rect)
    {
        return reinterpret_cast<SDL_Rect*>(const_cast<Rect *>(&rect));
    }

    inline std::ostream& operator<<(std::ostream& s, const Gambit::Rect &rc)
    {
        return s << '[' << rc.left << ", " << rc.top << ", " << rc.width << ", " << rc.height << ']';
    }
}

