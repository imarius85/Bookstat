#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>
#include <vector>

class Statistic
{
public:
    Statistic();
    ~Statistic();

    std::size_t fileSize;
    std::size_t wordCount;
    std::size_t lineCount;
    std::size_t phraseCount;
    std::size_t distinctWordCount;

    std::vector<std::string> wordList;

    std::size_t getSize() const;
    std::size_t getWordCount() const;
    std::size_t getPhraseCount() const;
    std::size_t getLineCount() const;
    std::size_t getDistinctWordCount() const;

    void reset();
    void update(const Statistic &newStat);
};

#endif // STATISTIC_H
