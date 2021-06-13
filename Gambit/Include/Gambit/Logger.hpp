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
        Warn = 4,
        Error = 8,
        Verbose = 16,
        None = 32,
    };

    class Logger
    {
        ELogLevel _logLevel;
        string _source;
        mutable std::stringstream _null;

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::Verbose);

        std::ostream& Info(const char* file, int line, const char *function) const;
        std::ostream& Debug(const char* file, int line, const char *function) const;
        std::ostream& Warn(const char* file, int line, const char *function) const;
        std::ostream& Error(const char* file, int line, const char *function) const;

    private:
        std::ostream& PrintLead(const char* file, int line, const char *func, rang::fg const &color, const char *level) const;
    };
}

#define LOG_INFO() \
    _log.Info(__FILE__, __LINE__, __FUNCTION__)

#define LOG_DEBUG() \
    _log.Debug(__FILE__, __LINE__, __FUNCTION__)

#define LOG_WARN() \
    _log.Warn(__FILE__, __LINE__, __FUNCTION__)

#define LOG_ERROR() \
    _log.Error(__FILE__, __LINE__, __FUNCTION__)

#define LOG_VALUE(X) \
    "\n\t\t" << rg::style::underline << rg::style::bold << rg::fg::blue << NAMEOF(X) << rg::style::reset << rg::fg::gray << "=" << X

