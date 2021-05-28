#pragma once

#include <string>
#include <iostream>
#include <sstream>

namespace ChessClock
{
    enum class ELogLevel
    {
        None = 0,
        Debug = 2,
        Verbose = 1,
        Error = 3,
    };

    class Logger
    {
        std::string _source;
        ELogLevel _logLevel;
        mutable std::stringstream _null;

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::None);

        std::ostream& Error(const char *file, int line) const;
        std::ostream& Debug(const char* file, int line) const;

    private:
        std::ostream& PrintLead(const char* file, int line, const char *level) const;
        std::ostream& Print(const char* file, int line, const char* level, const char* text) const;
    };
}

#define LOG_DEBUG() \
    _log.Debug(__FILE__, __LINE__)

#define LOG_ERROR() \
    _log.Error(__FILE__, __LINE__)

