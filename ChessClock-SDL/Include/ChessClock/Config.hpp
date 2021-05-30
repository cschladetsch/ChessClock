#pragma once

#include <memory>

namespace ChessClock
{
    template <class Ty>
    using shared_ptr = std::shared_ptr<Ty>;

    template <class Ty, class Alloc = std::allocator<Ty>>
    using vector = std::vector<Ty, Alloc>;

    using string = std::string;
}
