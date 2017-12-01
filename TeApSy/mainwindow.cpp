#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainboardwidget.h"
#include "i2crepresentationmodel.h"





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

    i2cTableView = new QTableView();

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
    QStringList horizontalHeader;
    horizontalHeader.append("Семибитный адрес");
    horizontalHeader.append("Восьмибитный адрес");
    horizontalHeader.append("Устройство");


    //Заголовки строк
    QStringList verticalHeader;
    verticalHeader.append("Ряд 1");
    verticalHeader.append("Ряд 2");

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    //Первый ряд
    item = new QStandardItem(QString("0"));
    model->setItem(0, 0, item);

    item = new QStandardItem(QString("1"));
    model->setItem(0, 1, item);

    item = new QStandardItem(QString("2"));
    model->setItem(0, 2, item);

//    item = new QStandardItem(QString("3"));
//    model->setItem(0, 3, item);

    //Второй ряд
    item = new QStandardItem(QString("4"));
    model->setItem(1, 0, item);

    item = new QStandardItem(QString("5"));
    model->setItem(1, 1, item);

    item = new QStandardItem(QString("6"));
    model->setItem(1, 2, item);

//    item = new QStandardItem(QString("7"));
//    model->setItem(1, 3, item);


    i2cTableView->setModel(model);


    ui->lt_I2C_DevicesFound->addWidget(i2cTableView);

    i2cTableView->resizeRowsToContents();
    i2cTableView->resizeColumnsToContents();
    i2cTableView->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    i2cTableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QRect rect = i2cTableView->geometry();
    rect.setWidth(2 + i2cTableView->columnWidth(0) + i2cTableView->columnWidth(1)+ i2cTableView->columnWidth(2));
    qDebug() << "Rectangle Width: " << 2  + i2cTableView->columnWidth(0) + i2cTableView->columnWidth(1)+ i2cTableView->columnWidth(2);
    //i2cTableView->setSizeAdjustPolicy()

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


