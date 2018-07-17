#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>

#include "Model/statistic.h"
#include "applogger.h"

class Book
{
    Statistic bookStatistics;

public:
    Book();
    Book(std::string path);
    ~Book();

    std::string path;
    std::fstream file;

    const std::string &getPath();
    Statistic &getStatistics();

    void runStatistics();
    void resetStatistics();
    static AppLogger *appLog;
};

#endif // BOOK_H
