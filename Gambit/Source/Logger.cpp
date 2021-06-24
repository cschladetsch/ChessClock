#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "Gambit/Logger.hpp"

//#ifdef WIN32
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#endif

// deprecated 'localtime'
#pragma warning (disable:4996)

namespace Gambit
{
    using namespace std;

    shared_ptr<fstream> Logger::_logFile;
    shared_ptr<teestream> Logger::_tee;
    string Logger::_logFileName;
    bool Logger::_triedOpenLogFile;

    Logger::Logger(const char *source, ELogLevel level)
        : _logLevel(level)
    {
        if (source == nullptr)
            return;

        _source = source;
        OpenLogFile();
    }

    void Logger::CloseFile()
    {
        if (_logFile && _logFile->good())
        {
            _logFile->close();
            _logFile.reset();
//#if WIN32
//            string code = "c:/Users/chris/AppData/Local/Programs/Microsoft\ VS\ Code/bin/code";
//            string cmd = R"--(c:\windows\system32\cmd.exe)--";
//            string exec = "start " + code + " " + _logFileName;
//            ShellExecute(0, "open", code.c_str(), _logFileName.c_str(), 0, SW_SHOWDEFAULT);
//            //system(exec.c_str());
//#endif
        }
    }

    bool Logger::OpenLogFile()
    {
        if (_logFile && _logFile->is_open())
            return true;
 
        if (_triedOpenLogFile)
            return false;

        _triedOpenLogFile = true;

        auto t = time(nullptr);
        auto tm = *localtime(&t);
        stringstream stream;
        stream << put_time(&tm, "ChessClock-%m-%d-%H-%M.txt") << ends;
        _logFileName = stream.str().c_str();
        try
        {
            _logFile = make_shared<fstream>(_logFileName.c_str(), fstream::out);
            if (_logFile->good())
            {
                _tee = make_shared<teestream>(*_logFile, cout);
            }
            return true;
        }
        catch (exception &e)
        {
            cerr << "Failed to open '" << _logFileName << "' log file for writing: " << e.what() << "\n";
        }

        return false;
    }

    ostream& Logger::Info(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Info <= _logLevel)
            return PrintLead(file, line, func, fg::green, "INFO");

        return _null;
    }

    ostream& Logger::Debug(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Debug <= _logLevel)
            return PrintLead(file, line, func, fg::cyan, "DEBUG");

        return _null;
    }

    ostream& Logger::Warn(const char* file, int line, const char *func) const
    {
        if (ELogLevel::Warn <= _logLevel)
            return PrintLead(file, line, func, fg::yellow, "WARN");

        return _null;
    }

    ostream& Logger::Error(const char* file, int line, const char *func) const
    {
        return PrintLead(file, line, func, fg::red, "ERROR");
    }

    ostream& Logger::PrintLead(const char* file, int line, const char *func, rang::fg const &color, const char *level) const
    {
        const char *lead = "";
        string fileName = file;
        auto fileNameLength = fileName.size();
        if (fileNameLength > 60)
        {
            fileName = "..." + fileName.substr(40);
        }
        auto millis = SDL_GetTicks()/1000.0f;
        stringstream stream;
        stream << style::reset << fg::reset << style::italic << fg::yellow << millis;
        stream << "ms: " << fg::reset << fg::gray << style::dim << fileName << "(" << line << "): ";
        stream << fg::cyan << func << fg::gray << ": " << style::bold << "\n";
        stream << "\t[" << color << level << fg::gray << "]: {" << fg::magenta << _source << fg::gray << "}:\n" << fg::blue;
        stream << "\t" << ends;
        auto str = stream.str();
        if (_tee)
            return *_tee << str;
        return cout << str;

        //if (_logFile)
        //{
        //    replace(str.begin(), str.end(), '\n', '|');
        //    *_logFile << str.c_str() << '\n';
        //    _logFile->flush();
        //}
        //return  << str;
    }
}

