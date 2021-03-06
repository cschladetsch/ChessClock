#pragma once

#include "SDL_stdinc.h"

namespace Gambit
{
    constexpr float FloatEps = 0.0001f;

    struct Vector2
    {
        int x{ 0 }, y{ 0 };

        Vector2() = default;
        Vector2(const Vector2 &other) = default;

        Vector2(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        friend Vector2 operator+(Vector2 const& left, Vector2 const& right)
        {
            return Vector2(left.x + right.x, left.y + right.y);
        }

        friend Vector2 operator-(Vector2 const& left, Vector2 const& right)
        {
            return Vector2(left.x - right.x, left.y - right.y);
        }

        friend bool operator==(Vector2 const& left, Vector2 const& right)
        {
            return SDL_fabs(left.x - right.x) < FloatEps && SDL_fabs(left.y - right.y) < FloatEps;
        }

        friend bool operator!=(Vector2 const& left, Vector2 const& right)
        {
            return !(left == right);
        }

        float Distance(Vector2 const& other) const
        {
            return SDL_sqrtf(static_cast<float>(other.x * x + other.y * y));
        }

        friend std::ostream& operator<<(std::ostream& out, const Vector2 &vec)
        {
            return out << "[ " << vec.x << ", " << vec.y << " ]";
        }
    };
}

