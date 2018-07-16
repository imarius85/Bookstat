#ifndef APPTHREAD_H
#define APPTHREAD_H

#include <QThread>

#include <memory>

#include "book.h"

class AppThread : public QThread
{
    Q_OBJECT
public:
    explicit AppThread(QThread *parent = nullptr);
    explicit AppThread(std::shared_ptr<Book> pBook);

    void run();

signals:
    void threadError();
    void threadFinished(std::shared_ptr<Book>);

public slots:

private:
    std::shared_ptr<Book> pBook;
    static AppLogger *appLog;
};

#endif // APPTHREAD_H
