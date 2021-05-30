#include "ChessClock/Logger.hpp"

namespace ChessClock
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
        if (_logLevel > ELogLevel::None)
            return PrintLead(file, line, "INFO");

        return _null;
    }

    std::ostream& Logger::Debug(const char* file, int line) const
    {
        if (_logLevel < ELogLevel::Debug)
            return PrintLead(file, line, "DEBUG");

        return _null;
    }

    std::ostream& Logger::Error(const char* file, int line) const
    {
        return PrintLead(file, line, "ERROR");
    }

    std::ostream& Logger::PrintLead(const char* file, int line, const char *level) const
    {
        return std::cout << file << "(" << line << "):" << " [" << level << "]: [[" << _source << "]]:\n\t";
    }

    std::ostream& Logger::Print(const char* file, int line, const char *level, const char* text) const
    {
        return PrintLead(file, line, level) << std::endl;
    }
}

