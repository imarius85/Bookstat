#include "applogger.h"

using namespace std;

string AppLogger::logName = "appLog.txt";
mutex  AppLogger::logMutex;
AppLogger *AppLogger::instance;

AppLogger::AppLogger()
{
    cout << "AppLogger()" << endl;

    logFile.open(logName, ios::app);
}

AppLogger::~AppLogger()
{
    if(logFile.is_open())
    {
        logFile.flush();
        logFile.close();
    }
}

AppLogger *AppLogger::getInstance()
{
    if(AppLogger::instance == nullptr)
        instance = new AppLogger();

    return instance;
}

void AppLogger::release()
{
    lock_guard<mutex> lg(logMutex);

    if(instance)
        delete instance;

    instance = nullptr;
}

void AppLogger::info(const string &message)
{
    lock_guard<mutex> lg(logMutex);

    cout << message << endl;

    if(logFile.is_open())
        logFile << message << endl;
    else
        cout << "Log file closed !";
}

void AppLogger::error(const string &message)
{
    lock_guard<mutex> lg(logMutex);

    cout << message << endl;

    if(logFile.is_open())
        logFile << message << endl;
    else
        cout << "Log file closed !";
}
