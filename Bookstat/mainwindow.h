#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

#include "book.h"
#include <map>
#include <memory>

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

public slots:
    void on_OpenFile_clicked();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void cm_runStatistics();
    void cm_resetStatistics();
    void cm_deleteItem();

    void tProcessingDone(std::shared_ptr<Book>);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
