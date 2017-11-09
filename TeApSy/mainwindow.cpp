#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainboardwidget.h"


//in order they are added in the void MainBoardWidget::setSipSapphireCommands() method
#define commandGETBOARDINFO 0
#define commandGETVOLTAGES 1
#define commandGETCURRENTS 2
#define commandGETTEMPERATURE 3
#define commandPERFORMI2CSCAN 4
#define commandBOARDRESET 5
#define commandCRYPTOENGINERESET 6
#define commandMAINCPURESET 7
#define commandENEXTPROGR 8
#define commandENINTPROGR 9
#define commandENAUTOLOGS 10



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _startDialog = new StartDialog();
    QObject::connect(_startDialog, &StartDialog::showMainWindow, this, &MainWindow::showMaximized);
    QObject::connect(_startDialog, &StartDialog::closeTheProgramm, this, &MainWindow::closeTheApp);
    QObject::connect(_startDialog, &StartDialog::showMainWindow, this, &MainWindow::updateTheBoardsData);
    //send the size to child widget;
    ui->wt_MainBoard->setMainWindowSize(size());

    //in order they are pushed to vector - see the constructor;
    connect(ui->btn_MeasureVoltages, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandGETVOLTAGES);});
    connect(ui->btn_ShowI2CDevices, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandPERFORMI2CSCAN);});
    connect(ui->btn_MeasureTemperatures, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandGETTEMPERATURE);});

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::startTheDialog()
{
    _startDialog->exec();
}

void MainWindow::closeTheApp()
{
    emit closeTheApplication(true);
}

void MainWindow::updateTheBoardsData()
{
    _boardsData = _startDialog->boardsData();
    _boardSelectedByUser = _startDialog->boardSelectedByUser();
    qDebug() << "Size of the MainWindow passed to the "
                "MainBoardWidget:" << size().height();
    //ui->wt_MainBoard->setMainWindowSize(size());
    ui->wt_MainBoard->setMainBoardWidgetPicturePath(_boardsData[_boardSelectedByUser].mainBoardWidgetPicturePath());
}


