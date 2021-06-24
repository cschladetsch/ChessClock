#pragma once

#include <fstream>

#include "Gambit/ThirdParty/nameof.hpp"
#include "Gambit/ThirdParty/ConsoleColor.hpp"

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ELogLevel.hpp"
#include "Gambit/TeeStream.hpp"

namespace Gambit
{
    class Logger
    {
        ELogLevel _logLevel;
        string _source;
        mutable std::stringstream _null;

        static std::shared_ptr<std::fstream> _logFile;
        static std::string _logFileName;
        static bool _triedOpenLogFile;
        static shared_ptr<teestream> _tee;

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::Verbose);
        static void CloseFile();

        std::ostream& Info(const char* file, int line, const char *function) const;
        std::ostream& Debug(const char* file, int line, const char *function) const;
        std::ostream& Warn(const char* file, int line, const char *function) const;
        std::ostream& Error(const char* file, int line, const char *function) const;

    private:
        bool OpenLogFile();
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
    "\t" << rg::style::underline << rg::style::bold << rg::fg::blue << NAMEOF(X) << rg::style::reset << rg::fg::gray << "=" << X

