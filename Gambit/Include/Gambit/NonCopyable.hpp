#pragma once

namespace Gambit
{
    struct NonCopyable
    {
        NonCopyable() {}

    private:
        NonCopyable(NonCopyable &) = delete;
        NonCopyable(NonCopyable &&) = delete;
        NonCopyable& operator =(NonCopyable &) = delete;
    };
}

