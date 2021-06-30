#include <stdexcept>

namespace Gambit
{
    class NotImplemented
        : public std::logic_error
    {
    public:
        NotImplemented(const char *text = "Not implemented")
            : std::logic_error(text) { }
    };
}

#define GAMBIT_NOT_IMPLEMENTED() \
    throw ::Gambit::NotImplemented();

#define GAMBIT_NOT_IMPLEMENTED_1(text) \
    throw ::Gambit::NotImplemented(text);

