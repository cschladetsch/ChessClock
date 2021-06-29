#pragma once

#include <sstream>

#include "Gambit/ThirdParty/nameof.hpp"
#include "Gambit/ThirdParty/ConsoleColor.hpp"

#include "Gambit/ForwardReferences.hpp"
#include "Gambit/ELogLevel.hpp"
#include "Gambit/TeeStream.hpp"

namespace Gambit
{
    class Logger
    {
        string _source;
        ELogLevel _logLevel;

        mutable std::stringstream _null;

        static bool _triedOpenLogFile;
        static string _logFileName;
        static shared_ptr<teestream> _tee;
        static shared_ptr<std::fstream> _logFile;
        static int _verbosityLevel;

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::Verbose);
        static void CloseFile();

        static void SetVerbosity(int level) { _verbosityLevel = level; }
        void Tee(std::ostream &other);

        using ostream = std::ostream;
        ostream& Info(const char *file, int line, const char *function) const;
        ostream& Verbose(const char *file, int line, const char *function, int level) const;
        ostream& Debug(const char *file, int line, const char *function) const;
        ostream& Warn(const char *file, int line, const char *function) const;
        ostream& Error(const char *file, int line, const char *function) const;

    private:
        bool OpenLogFile() const;
        ostream& PrintLead(const char *file, int line, const char *func, rang::fg const &color, const char *level) const;
    };
}

#define LOG_INFO() \
    _log.Info(__FILE__, __LINE__, __FUNCTION__)

#define LOG_DEBUG() \
    _log.Debug(__FILE__, __LINE__, __FUNCTION__)

#define LOG_WARN() \
    _log.Warn(__FILE__, __LINE__, __FUNCTION__)

#define LOG_VERBOSE(level) \
    _log.Verbose(__FILE__, __LINE__, __FUNCTION__, level)


#define LOG_ERROR() \
    _log.Error(__FILE__, __LINE__, __FUNCTION__)

//#define LOG_VALUE(X) \
//    rg::style::underline << rg::style::bold << rg::fg::blue << NAMEOF(X) << rg::style::reset << rg::fg::gray << "=" << X << " | "
#define LOG_VALUE(X) \
    rg::style::underline << rg::style::bold << rg::fg::blue << #X << rg::style::reset << rg::fg::gray << "=" << X << " | "

