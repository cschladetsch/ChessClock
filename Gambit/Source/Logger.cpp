#include "Gambit/Logger.hpp"

namespace Gambit
{
    Logger::Logger(const char* source, ELogLevel level)
        : _logLevel(level)
    {
        if (source == nullptr)
            return;

        _source = source;
    }

    std::ostream& Logger::Info(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Info <= _logLevel)
            return PrintLead(file, line, func, fg::green, "INFO");

        return _null;
    }

    std::ostream& Logger::Debug(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Debug <= _logLevel)
            return PrintLead(file, line, func, fg::cyan, "DEBUG");

        return _null;
    }

    std::ostream& Logger::Warn(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Warn <= _logLevel)
            return PrintLead(file, line, func, fg::yellow, "WARN");

        return _null;
    }

    std::ostream& Logger::Error(const char* file, int line, const char *func) const
    {
        return PrintLead(file, line, func, fg::red, "ERROR");
    }

    std::ostream& Logger::PrintLead(const char* file, int line, const char *func, rang::fg const &color, const char *level) const
    {
#if WIN32
        char *lead = "C:\\Users\\chris\\repos\\ChessClock\\";
#else
        char* lead = "/home/chris/ChessClock";
#endif
        string fl = file;
        fl = fl.substr(strlen(lead));
        auto millis = SDL_GetTicks()/1000.0f;
        std::cout << style::reset << fg::reset << style::italic << fg::yellow << millis;
        std::cout << "ms: " << fg::reset << fg::gray << style::dim << fl << "(" << line << "): ";
        std::cout << fg::cyan << func << fg::gray << ": " << style::bold << "\n";
        std::cout << "\t[" << color << level << fg::gray << "]: {" << fg::magenta << _source << fg::gray << "}:\n" << fg::blue;
        return std::cout << "\t";
    }
}

