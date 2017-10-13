#include "theloaderwindow.h"
#include "ui_theloaderwindow.h"

#define STARTUP_TIME_LOADER 3000 //defines the time that Loader Window Is Ative

TheLoaderWindow::TheLoaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheLoaderWindow)
{
    ui->setupUi(this);

    _startUpTimer = new QTimer(this);
    _startUpTimer->setSingleShot(true);
    connect(_startUpTimer, SIGNAL(timeout()), this, SLOT(startUpTimerEndCount()));
    _startUpTimer->start(STARTUP_TIME_LOADER);


}

TheLoaderWindow::~TheLoaderWindow()
{
    delete ui;
}

void TheLoaderWindow::startUpTimerEndCount()
{
    this->hide();
    emit startUpletsGo(true);
}
