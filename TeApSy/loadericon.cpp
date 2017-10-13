#include "loadericon.h"
#include "ui_loadericon.h"
#include <QDebug>
#include <QBitmap>

LoaderIcon::LoaderIcon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoaderIcon)
{
    ui->setupUi(this);

    QRect HW_Screen_Size = QApplication::desktop()->screenGeometry();
    int HW_Screen_Size_Width = HW_Screen_Size.width();
    int HW_Screen_Size_Height = HW_Screen_Size.height();
    const float loaderSize_Width = 0.2f*static_cast<float>(HW_Screen_Size_Width);
    const float loaderSize_Height = 0.143f*static_cast<float>(HW_Screen_Size_Height);
    const float sappHireLogo_Width = 0.2f*loaderSize_Width;
    const float sappHireLogo_Height =0.143f*loaderSize_Height;


    qDebug() << sappHireLogo_Height;
    qDebug() << sappHireLogo_Width;

//    QPixmap pxmp(":/Pictures/sapphireLogo.png");
//    qDebug() << pxmp.size().width();
//    qDebug() << pxmp.size().height();
//    ui->lblSapphire->setScaledContents(true);
//    ui->lblSapphire->setPixmap(pxmp);//.scaled(sappHireLogo_Width,sappHireLogo_Width,Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    ui->lblSapphire->setMask(pxmp.mask());
//    ui->lblSapphire->setMaximumSize(QSize(sappHireLogo_Width,sappHireLogo_Width));

    QPixmap pxmp2(":/Pictures/TeApSy_Loader_Test.png");
    qDebug() << pxmp2.size().width();
    qDebug() << pxmp2.size().height();
    //ui->lblGS->setScaledContents(true);
    //ui->lblGS->setAlignment(Qt::AlignHCenter);
    ui->lblGS->setPixmap(pxmp2);
    ui->lblGS->setMask(pxmp2.mask());

    //ui->lblGS->setMaximumSize(QSize(sappHireLogo_Width,sappHireLogo_Width));




}

LoaderIcon::~LoaderIcon()
{
    delete ui;
}
