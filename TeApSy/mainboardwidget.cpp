#include "mainboardwidget.h"
#include "ui_mainboardwidget.h"
#include "console.h"
#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>




MainBoardWidget::MainBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainBoardWidget)
{
    ui->setupUi(this);


    //set the picture
    QRect sizeOfScreen = QApplication::desktop()->screenGeometry();
    //the "Костыль". Up to refactor this
    //How to set the actual size of the Window to be present here?
    if ((_mainWindowSize.width() <= 0) ||
            (_mainWindowSize.width() > sizeOfScreen.width()) ||
            (_mainWindowSize.height() <= 0) ||
            (_mainWindowSize.height() > sizeOfScreen.height())
                                    ) {
        _mainWindowSize.setHeight(sizeOfScreen.height());
        _mainWindowSize.setWidth(sizeOfScreen.width());

    }






}

MainBoardWidget::~MainBoardWidget()
{
    delete ui;
}

QSize MainBoardWidget::mainWindowSize() const
{
    return _mainWindowSize;
}

void MainBoardWidget::setMainWindowSize(const QSize &mainWindowSize)
{
    _mainWindowSize = mainWindowSize;
}


void MainBoardWidget::setMainBoardWidgetPicturePath(const QString &_picturePath)
{

    QRect sizeOfScreen = QApplication::desktop()->screenGeometry();
    qDebug() << "Size of the screen aquired by MainBoardWidget: "
             << sizeOfScreen.height();


    constexpr double sizeOfMainBoardWidget = 1.5 / 4.0;
    double boardHorizontalSize = sizeOfScreen.width()*sizeOfMainBoardWidget;
    double boardVerticalSize = sizeOfScreen.height()*sizeOfMainBoardWidget;



    qDebug() << "Vertical size of MainBoard Widget Picture: " << boardVerticalSize;
    QImage newImage(_picturePath);
    QPixmap somePixmap;
    somePixmap.convertFromImage(newImage,Qt::ImageConversionFlag::AutoColor);
    //boardHorizontalSize = sizeOfScreen.width() - 100;
    qDebug() << "Horizontal size of MainBoard Widget Picture: " << boardVerticalSize;
    QPalette somePalette;
    QBrush someBrush(QBrush(somePixmap.scaled(static_cast<int>(boardHorizontalSize), static_cast<int>(boardVerticalSize),
                                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));




    ui->btn_MainBoard->setMinimumHeight(static_cast<int>(boardVerticalSize));
    ui->btn_MainBoard->setMinimumWidth(static_cast<int>(boardHorizontalSize));
    ui->btn_MainBoard->setMaximumHeight(static_cast<int>(boardVerticalSize));
    ui->btn_MainBoard->setMaximumWidth(static_cast<int>(boardHorizontalSize));

    somePalette.setBrush(ui->btn_MainBoard->backgroundRole(),
                         someBrush);

    ui->btn_MainBoard->setFlat(true);
    ui->btn_MainBoard->setAutoFillBackground(true);
    ui->btn_MainBoard->setPalette(somePalette);
}

