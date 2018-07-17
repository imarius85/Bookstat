#include <iostream>
#include <sstream>
#include <memory>

#include "appthread.h"

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

    Statistic newStat;

    newStat.reset();

    try{

        pBook.get()->file.open(pBook.get()->path);

        int no_lines = count(std::istreambuf_iterator<char>(pBook.get()->file),
                             std::istreambuf_iterator<char>(), '\n');

        pBook.get()->file.seekg( 0 );

        if(pBook.get()->file.is_open())
        {
            string fileLine;

            while(!pBook.get()->file.eof())
            {
                getline(pBook.get()->file, fileLine);

                newStat.lineCount++;

                string token;
                stringstream ss(fileLine);

                while(ss >> token)
                {
                    newStat.wordCount++;
                }

                if(!(newStat.lineCount % 10))
                    emit threadProcessing(pBook, (newStat.lineCount*100/no_lines));

                msleep(10);
            }
        }

        pBook.get()->file.close();

        pBook.get()->getStatistics().update(newStat);
    }
    catch(exception ex)
    {
        appLog->error(ex.what());
        emit threadError();
    }

    emit threadFinished(pBook);
}
