#include <qstring.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qprogressbar.h>

#include <fstream>
#include <memory>
#include <future>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appthread.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qRegisterMetaType<std::shared_ptr<Book>>("std::shared_ptr<Book>");

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTableRow(shared_ptr<Book> newBook, size_t row_id)
{
    int col_id = 0;

    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::fromStdString(newBook.get()->getPath())));
    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::number(newBook.get()->getStatistics().getPhraseCount())));
    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::number(newBook.get()->getStatistics().getWordCount())));
    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::number(newBook.get()->getStatistics().getDistinctWordCount())));
    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::number(newBook.get()->getStatistics().getLineCount())));
    ui->tableWidget->setItem(row_id, col_id++, new QTableWidgetItem(QString::number(newBook.get()->getStatistics().getSize())));
    ui->tableWidget->setCellWidget(row_id, col_id++, new QProgressBar());
}

void MainWindow::updateTableAddItem(shared_ptr<Book> newBook)
{
    int row_id = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(row_id);

    setTableRow(newBook, row_id);
}

void MainWindow::updateTableUpdateItem(shared_ptr<Book> newBook)
{
    for(auto row_id = 0; row_id < ui->tableWidget->rowCount(); row_id++)
    {
        string rowBook = ui->tableWidget->item(row_id, 0)->text().toStdString();

        if(rowBook.compare(newBook.get()->getPath()) == 0)
        {
            setTableRow(newBook, row_id);
            break;
        }
    }
}

void MainWindow::updateTableUpdateItem(shared_ptr<Book> newBook, int percentage)
{
    for(auto row_id = 0; row_id < ui->tableWidget->rowCount(); row_id++)
    {
        string rowBook = ui->tableWidget->item(row_id, 0)->text().toStdString();

        if(rowBook.compare(newBook.get()->getPath()) == 0)
        {
            QProgressBar *ptr = dynamic_cast<QProgressBar *>(ui->tableWidget->cellWidget(row_id, 6));
            if(ptr)
                ptr->setValue(percentage);

            break;
        }
    }
}

void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    QMenu *menu=new QMenu(this);

    QAction *a_runStatistic     = new QAction("Run statistics", this);
    QAction *a_resetStatistic   = new QAction("Reset statistics", this);
    QAction *a_deleteItem       = new QAction("Delete item", this);

    menu->connect(a_runStatistic,    SIGNAL(triggered()), this, SLOT(cm_runStatistics()));
    menu->connect(a_resetStatistic,  SIGNAL(triggered()), this, SLOT(cm_resetStatistics()));
    menu->connect(a_deleteItem,      SIGNAL(triggered()), this, SLOT(cm_deleteItem()));

    menu->addAction(a_runStatistic);
    menu->addAction(a_resetStatistic);
    menu->addAction(a_deleteItem);

    menu->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::cm_runStatistics()
{
    try
    {
        QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes();

        if(indexList.isEmpty())
            return;

        string fileName = ui->tableWidget->item(indexList.first().row(), 0)->text().toStdString();

        if(bookCollection.find(fileName) != bookCollection.end())
        {
            AppThread *newThread = new AppThread(bookCollection[fileName]);

            connect(newThread,    SIGNAL(threadFinished(std::shared_ptr<Book>)), this, SLOT(tProcessingDone(std::shared_ptr<Book>)));
            connect(newThread,    SIGNAL(threadProcessing(std::shared_ptr<Book>, int)), this, SLOT(tProcessing(std::shared_ptr<Book>, int)));

            newThread->start();
        }
    }
    catch(exception ex)
    {
        cout << "Unhandled exception - " << ex.what() << endl;
    }
}

void MainWindow::cm_resetStatistics()
{
    try
    {
        QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes();

        if(indexList.isEmpty())
            return;

        string fileName = ui->tableWidget->item(indexList.first().row(), 0)->text().toStdString();

        bookCollection[fileName].get()->resetStatistics();

        setTableRow(bookCollection[fileName], indexList.first().row());
    }
    catch(exception ex)
    {
        cout << "Unhandled exception - " << ex.what() << endl;
    }
}

void MainWindow::cm_deleteItem()
{
    try
    {
        QModelIndexList indexList = ui->tableWidget->selectionModel()->selectedIndexes();

        if(indexList.isEmpty())
            return;

        string fileName = ui->tableWidget->item(indexList.first().row(), 0)->text().toStdString();

        bookCollection.erase(fileName);

        ui->tableWidget->removeRow(indexList.first().row());
    }
    catch(exception ex)
    {
        cout << "Unhandled exception - " << ex.what() << endl;
    }
}

void MainWindow::tProcessingDone(std::shared_ptr<Book> pBook)
{
    updateTableUpdateItem(pBook);
}

void MainWindow::tProcessing(std::shared_ptr<Book> pBook, int percentage)
{
    updateTableUpdateItem(pBook, percentage);
}

void MainWindow::on_OpenFile_clicked()
{
    try{
        string fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "D:\\", tr("Text files (*.txt)")).toStdString();

        if(!fileName.size())
            return;

        if(bookCollection.find(fileName) == bookCollection.end())
        {
            shared_ptr<Book> newBook(new Book(fileName));

            bookCollection.insert(make_pair(fileName, newBook));
            updateTableAddItem(bookCollection[fileName]);
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Book already present !");
            msgBox.exec();
        }
    }
    catch(exception ex)
    {
        cout << "Unhandled exception - " << ex.what() << endl;
    }
}
