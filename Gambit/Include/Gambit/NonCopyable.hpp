#pragma once

namespace Gambit
{
    struct NonCopyable
    {
    protected:
        ~NonCopyable() = default;

    public:
        NonCopyable() = default;

        NonCopyable(NonCopyable &) = delete;
        NonCopyable(NonCopyable &&) = delete;
        NonCopyable& operator =(NonCopyable &) = delete;
    };
}

