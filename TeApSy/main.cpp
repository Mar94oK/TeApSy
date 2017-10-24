#include "mainwindow.h"
#include "theloaderwindow.h"

#include <QApplication>
#include <QTimer>
#include <QRect>
#include <QDesktopWidget>
#include <applicationsettings.h>
#include <version.h>
#include <QDebug>
#include <QLabel>


int main(int argc, char *argv[])
{

    //check the revision first
    if (releaseRevision != VER) {
        qDebug() << "ERROR IN REVISION SETTINGS!";

    }



    QApplication a(argc, argv);
    MainWindow w;
    TheLoaderWindow lw;
    //QObject::connect(&lw, SIGNAL(startUpletsGo(bool)), &w, SLOT(show()));
    QObject::connect(&lw, &TheLoaderWindow::startUpletsGo, &w, &MainWindow::startTheDialog);
    QObject::connect(&w, &MainWindow::closeTheApplication, &a, QApplication::quit);
    lw.show();





    return a.exec();
}
