#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>

#include "statistic.h"
#include "applogger.h"

class Book
{
    std::string path;
    Statistic bookStatistics;
    std::fstream file;

public:
    Book();
    Book(std::string path);
    ~Book();

    const std::string &getPath();
    Statistic &getStatistics();

    void runStatistics();
    void resetStatistics();
    static AppLogger *appLog;
};

#endif // BOOK_H
