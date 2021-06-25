#pragma once

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

    public:
        Logger(const char* source, ELogLevel logLevel = ELogLevel::Verbose);
        static void CloseFile();

        void Tee(std::ostream &other);

        std::ostream& Info(const char *file, int line, const char *function) const;
        std::ostream& Debug(const char *file, int line, const char *function) const;
        std::ostream& Warn(const char *file, int line, const char *function) const;
        std::ostream& Error(const char *file, int line, const char *function) const;

    private:
        bool OpenLogFile();
        std::ostream& PrintLead(const char *file, int line, const char *func, rang::fg const &color, const char *level) const;
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

//#define LOG_VALUE(X) \
//    rg::style::underline << rg::style::bold << rg::fg::blue << NAMEOF(X) << rg::style::reset << rg::fg::gray << "=" << X << " | "
#define LOG_VALUE(X) \
    rg::style::underline << rg::style::bold << rg::fg::blue << #X << rg::style::reset << rg::fg::gray << "=" << X << " | "

