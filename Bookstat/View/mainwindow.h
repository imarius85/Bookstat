#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <map>
#include <memory>

#include "Model/book.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    map<string, shared_ptr<Book>> bookCollection;

    void setTableRow(shared_ptr<Book> newBook, size_t row_id);

    void updateTableAddItem(shared_ptr<Book> newBook);
    void updateTableUpdateItem(shared_ptr<Book> newBook);
    void updateTableUpdateItem(shared_ptr<Book> newBook, int percentage);

public slots:
    void on_OpenFile_clicked();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void cm_runStatistics();
    void cm_resetStatistics();
    void cm_deleteItem();

    void tProcessingDone(std::shared_ptr<Book>);
    void tProcessing(std::shared_ptr<Book>, int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
