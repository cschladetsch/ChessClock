#pragma once

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ThirdParty/nameof.hpp"
#include "Gambit/ThirdParty/ConsoleColor.hpp"

namespace Gambit
{
    enum class ELogLevel
    {
        Info = 1,
        Debug = 2,
        Warn = 3,
        Error = 4,
        Verbose = 5,
        None = 6,
    };

    class Logger
    {
        ELogLevel _logLevel;
        string _source;
        mutable std::stringstream _null;

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::Verbose);

        std::ostream& Info(const char* file, int line) const;
        std::ostream& Debug(const char* file, int line) const;
        std::ostream& Warn(const char* file, int line) const;
        std::ostream& Error(const char* file, int line) const;

    private:
        std::ostream& PrintLead(const char* file, int line, rang::fg const &color, const char *level) const;
        std::ostream& Print(const char* file, int line, const char* level, const char* text) const;
    };
}

#define LOG_INFO() \
    _log.Info(__FILE__, __LINE__)

#define LOG_DEBUG() \
    _log.Debug(__FILE__, __LINE__)

#define LOG_WARN() \
    _log.Warn(__FILE__, __LINE__)

#define LOG_ERROR() \
    _log.Error(__FILE__, __LINE__)

#define LOG_VALUE(X) \
    " | " << ::rang::style::underline << NAMEOF(X) << ::rang::style::reset << ::rang::fg::green << "=" << X

