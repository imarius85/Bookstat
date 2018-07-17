#include <QApplication>

#include "View/mainwindow.h"
#include "applogger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    AppLogger *appLog = AppLogger::getInstance();

    appLog->info("Starting Bookstat application..");

    return a.exec();
}
