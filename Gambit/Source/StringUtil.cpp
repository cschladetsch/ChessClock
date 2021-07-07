#include <codecvt>
#include <locale>
#include <string>

namespace Gambit
{
#ifdef WIN32
    #pragma warning (disable:4996)
#endif

    std::string NarrowString(const std::wstring &str)
    {
        std::wstring_convert<
            std::codecvt_utf8_utf16< std::wstring::value_type >,
            std::wstring::value_type
        > utf16conv;
        return utf16conv.to_bytes(str);
    }
}

