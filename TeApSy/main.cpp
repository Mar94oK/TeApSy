#include "mainwindow.h"
#include "theloaderwindow.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    TheLoaderWindow lw;
    QObject::connect(&lw, SIGNAL(startUpletsGo(bool)), &w, SLOT(show()));

    lw.show();

    return a.exec();
}
