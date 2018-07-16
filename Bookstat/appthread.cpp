#include "appthread.h"

#include <iostream>
#include <memory>

using namespace std;

AppLogger* AppThread::appLog = AppLogger::getInstance();

AppThread::AppThread(QThread *parent) : QThread(parent)
{
}

AppThread::AppThread(shared_ptr<Book> pBook) : QThread(nullptr)
{
    this->pBook = pBook;
}

void AppThread::run()
{
    appLog->info("Start processing book statistics..");

    try
    {
        pBook->runStatistics();
    }
    catch(exception ex)
    {
        appLog->error(ex.what());
        emit threadError();
    }

    emit threadFinished(pBook);
}
