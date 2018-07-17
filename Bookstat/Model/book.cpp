#include <QThread>
#include <sstream>

#include "Model/book.h"
#include "applogger.h"

using namespace std;

AppLogger* Book::appLog = AppLogger::getInstance();

Book::Book()
{   
}

Book::Book(string path)
{
    this->path = path;
    this->resetStatistics();
}

Book::~Book()
{
}

const std::string &Book::getPath()
{
    return this->path;
}

Statistic &Book::getStatistics()
{
    return this->bookStatistics;
}

void Book::runStatistics()
{
    Statistic newStat;

    newStat.reset();

    appLog->info("runStatistics..");

    try{

        file.open(path);

        if(file.is_open())
        {
            string fileLine;

            while(!file.eof())
            {
                getline(file, fileLine);

                newStat.lineCount++;

                string token;
                stringstream ss(fileLine);

                while(ss >> token)
                {
                    newStat.wordCount++;
                }
            }
        }

        file.close();

        this->bookStatistics.update(newStat);
    }
    catch(exception ex)
    {
        appLog->error("runStatistics exception !");
    }
}

void Book::resetStatistics()
{
    this->bookStatistics.reset();
}
