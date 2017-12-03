#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainboardwidget.h"
#include "i2crepresentationmodel.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , i2cTableModel(new I2cRepresentationModel(this))
{
    ui->setupUi(this);
    _startDialog = new StartDialog();
    QObject::connect(_startDialog, &StartDialog::showMainWindow, this, &MainWindow::showMaximized);
    QObject::connect(_startDialog, &StartDialog::closeTheProgramm, this, &MainWindow::closeTheApp);
    QObject::connect(_startDialog, &StartDialog::showMainWindow, this, &MainWindow::updateTheBoardsData);
    //send the size to child widget;
    ui->wt_MainBoard->setMainWindowSize(size());

    ui->i2cView->setModel(i2cTableModel);
    i2cTableModel->addDevice("40|name1");
    i2cTableModel->addDevice("41|name2");
    ui->i2cView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    //in order they are pushed to vector - see the constructor;
    connect(ui->btn_MeasureVoltages, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandGETVOLTAGES);});
    connect(ui->btn_ShowI2CDevices, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandPERFORMI2CSCAN);});
    connect(ui->btn_MeasureTemperatures, &QPushButton::clicked, [this]{ui->wt_MainBoard->sendCommand(commandGETTEMPERATURE);});

    //updatingValues
    connect(ui->wt_MainBoard, &MainBoardWidget::voltageCurrentDataIsReady, this, &MainWindow::updateVoltageCurrentData);
    connect(this, &MainWindow::signal_updateVoltageCurrentData, ui->wt_MeasuredValues, &MeasuredValues::updateValues);

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
    qDebug() << "Board_Selected_By_User" << _boardSelectedByUser;
    //ui->wt_MainBoard->setMainWindowSize(size());
    ui->wt_MainBoard->setMainBoardWidgetPicturePath(_boardsData[_boardSelectedByUser].mainBoardWidgetPicturePath());

    if (_boardSelectedByUser == 0) { //sipSapphire //

        for (int var = 0; var < 15; ++var) {
            ui->wt_MeasuredValues->addPairsWidgets();
        }



    }





}

void MainWindow::updateVoltageCurrentData(std::vector<VoltageCurrentData> newdata)
{
    emit signal_updateVoltageCurrentData(newdata);
}


