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

    std::ostream& Logger::Info(const char* file, int line) const
    {
        if (ELogLevel::Info <= _logLevel)
            return PrintLead(file, line, fg::green, "INFO");

        return _null;
    }

    std::ostream& Logger::Debug(const char* file, int line) const
    {
        if (ELogLevel::Debug <= _logLevel)
            return PrintLead(file, line, fg::cyan, "DEBUG");

        return _null;
    }

    std::ostream& Logger::Warn(const char* file, int line) const
    {
        if (ELogLevel::Warn <= _logLevel)
            return PrintLead(file, line, fg::yellow, "WARN");

        return _null;
    }

    std::ostream& Logger::Error(const char* file, int line) const
    {
        return PrintLead(file, line, fg::red, "ERROR");
    }

    std::ostream& Logger::PrintLead(const char* file, int line, rang::fg const &color, const char *level) const
    {
#if WIN32
        char *lead = "C:\\Users\\chris\\repos\\ChessClock\\";
#else
        char* lead = "/home/chris/ChessClock";
#endif
        string fl = file;
        fl = fl.substr(strlen(lead));
        return std::cout << fg::reset << fg::gray << style::dim << fl << "(" << line << "):" << style::bold << " [" << color <<  level << fg::gray << "]: {" << fg::magenta << _source << fg::gray << "}:\n" << fg::blue;
    }
}

