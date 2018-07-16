#ifndef APPLOGGER_H
#define APPLOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>

class AppLogger
{    
    static AppLogger *instance;
    static std::mutex logMutex;

    std::fstream logFile;

    AppLogger();
    ~AppLogger();

public:
    static std::string logName;

    static AppLogger *getInstance();
    static void release();

    void info (const std::string &message);
    void error(const std::string &message);
};

#endif // APPLOGGER_H
