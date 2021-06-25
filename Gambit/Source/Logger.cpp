#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "Gambit/Logger.hpp"

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
        _logFileName = stream.str();
        try
        {
            _logFile = make_shared<fstream>(_logFileName.c_str(), fstream::out);
            if (_logFile->good())
            {
                //_tee = make_shared<teestream>(*_logFile, cout);
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
            return PrintLead(file, line, func, fg::green, "INFO ");

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
            return PrintLead(file, line, func, fg::yellow, "WARN ");

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
        if (fileNameLength > 33)
        {
            fileName = "..." + fileName.substr(fileNameLength - 30);
        }
        ostream &stream = _tee ? *_tee : cout;
        //auto millis = SDL_GetTicks()/1000.0f;
        //stream << style::reset << fg::reset << style::italic << fg::yellow << millis;
        //stream << "ms: " << fg::reset << fg::gray << style::dim << fileName << "(" << line << "): ";
        //stream << fg::cyan << func << fg::gray << ": " << style::bold << "\n";
        //stream << "\t[" << color << level << fg::gray << "]: {" << fg::magenta << _source << fg::gray << "}:\n" << fg::blue;
        //stream << "\t" << ends;

        stream << style::reset << fg::reset;
        stream << "[" << color << level << fg::gray << "]: {" << fg::magenta << _source << fg::gray << "}: ";
        stream << style::dim << fileName << "(" << line << "): ";
        stream << fg::cyan << func << fg::gray << ": " << style::bold << "\n";
        stream << "\t" << ends;
        return stream;
    }
}

