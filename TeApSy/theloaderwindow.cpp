#include "theloaderwindow.h"
#include "ui_theloaderwindow.h"
#include <QDebug>
#include <QBitmap>



TheLoaderWindow::TheLoaderWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TheLoaderWindow)
{
    ui->setupUi(this);

    //how to disable top menu
    this->setWindowFlags(Qt::FramelessWindowHint);




    _startUpTimer = new QTimer(this);
    _startUpTimer->setSingleShot(true);
    connect(_startUpTimer, SIGNAL(timeout()), this, SLOT(startUpTimerEndCount()));
    _startUpTimer->start(STARTUP_TIME_LOADER);



    //QPixmap pxmp2(":/Pictures/TeApSy_Loader_Test.png");
   // QBitmap btMap(":/Pictures/TeApSy_Loader_Test.png");


    QPixmap pxmp2(":/Pictures/TeApSy_ldr.jpg");
    QBitmap btMap(":/Pictures/TeApSy_Loader_Test.png");

    //setMask(btMap);


    QPalette plte;
    plte.setBrush(this->backgroundRole(), QBrush(pxmp2));
    setAutoFillBackground(true);
    setPalette(plte);



    //setFixedHeight(pxmp2.height());
    //setFixedWidth(pxmp2.width());
    //this->setMask(pxmp2)
    //setMask(pxmp2);
    qDebug() << pxmp2.size().width();
    qDebug() << pxmp2.size().height();
    //ui->lblGS->setScaledContents(true);
    //ui->lblGS->setAlignment(Qt::AlignHCenter);



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
