#-------------------------------------------------
#
# Project created by QtCreator 2018-07-10T13:17:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bookstat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    Model/book.cpp \
    Model/statistic.cpp \
    Controller/appthread.cpp \
    View/mainwindow.cpp \
    applogger.cpp \
    main.cpp \
    Model/appmodel.cpp \
    View/appview.cpp \
    Controller/appcontroller.cpp

HEADERS += \
    Model/book.h \
    Model/statistic.h \
    Controller/appthread.h \
    View/mainwindow.h \
    applogger.h \
    Model/appmodel.h \
    View/appview.h \
    Controller/appcontroller.h

FORMS += \
        mainwindow.ui

DISTFILES += \
    DesignProposal
