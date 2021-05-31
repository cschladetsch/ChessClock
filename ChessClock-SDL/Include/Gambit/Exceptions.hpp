#include <exception>

namespace Gambit
{
    class NotImplemented : public std::logic_error
    {
    public:
        NotImplemented() : std::logic_error("Not implemented") { }
    };
}
