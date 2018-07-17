#include <algorithm>

#include "Model/statistic.h"

using namespace  std;

Statistic::Statistic()
{
}

Statistic::~Statistic()
{
}

std::size_t Statistic::getSize() const
{
    return fileSize;
}

std::size_t Statistic::getWordCount() const
{
    return wordCount;
}

std::size_t Statistic::getPhraseCount() const
{
    return phraseCount;
}

size_t Statistic::getLineCount() const
{
    return lineCount;
}

std::size_t Statistic::getDistinctWordCount() const
{
    return distinctWordCount;
}

void Statistic::reset()
{
    this->fileSize = 0;
    this->wordCount = 0;
    this->lineCount = 0;
    this->phraseCount = 0;
    this->distinctWordCount = 0;

    this->wordList.clear();
}

void Statistic::update(const Statistic &newStat)
{
    this->reset();

    this->distinctWordCount = newStat.distinctWordCount;
    this->fileSize = newStat.fileSize;
    this->lineCount = newStat.lineCount;
    this->phraseCount = newStat.phraseCount;
    this->wordCount = newStat.wordCount;

    copy(newStat.wordList.begin(), newStat.wordList.end(), back_inserter(this->wordList));
}
