#-------------------------------------------------
#
# Project created by QtCreator 2017-10-13T16:42:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets




VERSION = 0.00.0000

#QMAKE_TARGET_COMPANY = GS Labs
#QMAKE_TARGET_PRODUCT = TeApSy
#QMAKE_TARGET_DESCRIPTION = Set-Top Box Automatic Test System
#QMAKE_TARGET_COPYRIGHT = Maxim Uvarenkov

TARGET = TeApSy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    loadericon.cpp \
    theloaderwindow.cpp \
    sipsapphirerefboard.cpp \
    startdialog.cpp \
    boardrepresentation.cpp

HEADERS  += mainwindow.h \
    loadericon.h \
    theloaderwindow.h \
    sipsapphirerefboard.h \
    startdialog.h \
    applicationsettings.h \
    boardrepresentation.h \
    version.h

FORMS    += mainwindow.ui \
    loadericon.ui \
    theloaderwindow.ui \
    startdialog.ui \
    boardrepresentation.ui

RESOURCES += \
    pictures.qrc \
    tables.qrc \
    aboutboards.qrc

RC_FILE = TeApSy.rc
