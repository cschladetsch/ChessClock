#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Gambit
{
    template <class Ty>
    using shared_ptr = std::shared_ptr<Ty>;

    template <class Ty, class Alloc = std::allocator<Ty>>
    using vector = std::vector<Ty, Alloc>;

    using string = std::string;
}

#define CALL_BOOL(X) \
    do {\
        if (!(X)) \
        { \
            LOG_ERROR() << LOG_VALUE(#X) << "\n"; \
            return false; \
        } \
    } while (0)

