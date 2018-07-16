#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <fstream>

#include "statistic.h"
#include "applogger.h"

class Book
{
    std::string path;
    std::string bookName;
    std::string bookAuthor;

    Statistic bookStatistics;

    std::fstream file;
public:
    Book();
    Book(std::string path);
    Book(std::string path, std::string name, std::string author);
    ~Book();

    const std::string &getName();
    const std::string &getAuthor();
    const std::string &getPath();
    Statistic &getStatistics();

    void runStatistics();
    void resetStatistics();
    static AppLogger *appLog;
};

#endif // BOOK_H
