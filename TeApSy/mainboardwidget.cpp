#include "mainboardwidget.h"
#include "ui_mainboardwidget.h"
#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPort>
#include <QTime>




void waitms(int ms) {
    QTime time;
    time.start();
    for (;time.elapsed() < ms;)
    {
    }


}



MainBoardWidget::MainBoardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainBoardWidget)
{
    ui->setupUi(this);


    _settings = new SettingsDialog();
    _mainCPUport = new QSerialPort(this);
    _cryptoEnginePort = new QSerialPort(this);


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

    //buttons for Debug

    ui->btn_OpenPort->setMaximumWidth(static_cast<int>(static_cast<double>(sizeOfScreen.width())*(1.5 / 4.0)));
    ui->btn_ClosePort->setMaximumWidth(static_cast<int>(static_cast<double>(sizeOfScreen.width())*(1.5 / 4.0)));
    ui->btn_OpenPort->setMinimumWidth(static_cast<int>(static_cast<double>(sizeOfScreen.width())*(1.5 / 4.0)));
    ui->btn_ClosePort->setMinimumWidth(static_cast<int>(static_cast<double>(sizeOfScreen.width())*(1.5 / 4.0)));

    ui->lt_dbgControls->setAlignment(Qt::AlignHCenter);
    //set serial Ports;

    connect(_mainCPUport, &QSerialPort::readyRead, this, &MainBoardWidget::readData);
    connect(ui->logsMainProcessor, &Console::getData, this, &MainBoardWidget::writeData);

    ui->logsCryptoProcessor->setEnabled(false);
    ui->logsMainProcessor->setEnabled(false);

    //set here all the commands
    setSipSapphireCommands();

    initActionsConnections();


    //create ReportTimeOutTimer;

    waitForReportTimer = new QTimer(this);
    waitForReportTimer->setSingleShot(true);

    connect (waitForReportTimer, &QTimer::timeout, this, &MainBoardWidget::resetTheWaitingState);
    connect (this, &MainBoardWidget::signal_stopTheWaitForReportTimer,
             this, &MainBoardWidget::stopTheWaitforReportTimer);












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

void MainBoardWidget::initActionsConnections()
{
    //connect(ui->)
    connect(ui->btn_Settings, &QPushButton::pressed, _settings, &SettingsDialog::show);
    connect(ui->btn_OpenPort, &QPushButton::pressed, this, &MainBoardWidget::openSerialPort);
    connect(ui->btn_ClosePort, &QPushButton::pressed, this, &MainBoardWidget::closeSerialPort);
    
}

bool MainBoardWidget::ucReportsReceiver(QString reportData)
{
    bool reportIsComplete = false;
    _ucReportsData += reportData; //all in one!
//    QStringList list = reportData.split("|\r\n");
//    for (int var = 0; var < list.size(); ++var) {
//        _reportsData.push_back(list[var]);
//        if (list[var] == "sysReportEND;") { reportIsComplete = true;
//        }
//    }

//    return reportIsComplete;
    if (_ucReportsData.contains(QString("sysReportEND"))) {
        reportIsComplete = true;
    }
    return reportIsComplete;
    
    
    
}

void MainBoardWidget::ucReportsParser()
{
    //qDebug() << "Parsing starts!" ;
    QString filename = "F:\\Logs\\Data.txt";
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    stream << "\r\n";

    //fisrt write the data to file;

    stream << _ucReportsData;

    //next choose the parser for data and prepare it; aftewards send to the MainWindow or another Widget to show;

    bool isCurrentVoltagesReport = false;
    bool isI2CReport = false;



    if (_ucReportsData.contains(QString("sysReportVoltagesCurrents"))) {
        isCurrentVoltagesReport = true;
    }
    if (_ucReportsData.contains(QString("sysReportI2CScanResults"))) {
        isI2CReport = true;
    }

    if (isCurrentVoltagesReport) {
        std::vector<VoltageCurrentData> _voltageCurrentDataReceived;
         QStringList list =_ucReportsData.split("|");
         for (int var = 1; var < list.size() - 1; ++var) { //disable endings
             QStringList containsList = list[var].split(";");
             VoltageCurrentData vcData;
             vcData._name = containsList.first();
             containsList.removeFirst();
             vcData._valueVoltage = containsList.first().toFloat();
             containsList.removeFirst();
             vcData._valueCurrent = containsList.first().toFloat();
             //end of parsing, put the structure to vector;
             _voltageCurrentDataReceived.push_back(vcData);

         }


        emit voltageCurrentDataIsReady(_voltageCurrentDataReceived);
        //report, that Report Is Ready!
        //voltageReportIsReady = true;
        setIsWatingForReport(false);
        voltageCurrentScanIsPerforming = false;
        emit signal_stopTheWaitForReportTimer();
    }

    else if (isI2CReport) {

        std::vector<I2CDevice> _i2cAddressesReceived;
        //up to develop

        //std::vector<I2CDevice> _i2cAddressesReceivedSecondScan;
        //std::vector<I2CDevice> _i2cAddressesReceivedThirdScan;

        QStringList list = _ucReportsData.split("|");
        //later to develop all the three scans;
        //first, found where is the real data;
        QStringList listTotalScans  = list[2].split(";");
        listTotalScans.removeFirst();
        int totalScansPerformed = listTotalScans.first().toInt();
        int stringWithCurrentResult = 0;

        if (!(totalScansPerformed % 2)) {
            stringWithCurrentResult = 2;
        }
        else if (!(totalScansPerformed % 3)) {
            stringWithCurrentResult = 3;
        }
        else {
            stringWithCurrentResult = 1;
        }




        QStringList containsList = list[1+stringWithCurrentResult].split(";");
        for (int s = 2; s < containsList.size(); ++s) { //scip first two values
            I2CDevice devData;
            devData._I2CdeviceAddress = containsList.first();
            _i2cAddressesReceived.push_back(devData);

        }
        emit i2cDeviceDataIsReady(_i2cAddressesReceived);

        //report, that Report Is Ready!
        //i2cReportIsReady = true;
        //i2cScanIsPerfroming = false;
        setIsWatingForReport(false);
        i2cScanIsPerforming = false;
        emit signal_stopTheWaitForReportTimer();

    }
//    else {
//        setIsWatingForReport(false);
//    }




    //clear vector if neccessary
    //clear the string

    _reportsData.clear();
    _ucReportsData.clear();


    file.close();



}

//bool MainBoardWidget::getI2cReportIsReady() const
//{
//    return i2cReportIsReady;
//}

bool MainBoardWidget::getIsWatingForReport() const
{
    return isWatingForReport;
}

void MainBoardWidget::setIsWatingForReport(bool value)
{
    isWatingForReport = value;
}

//bool MainBoardWidget::getVoltageReportIsReady() const
//{
//    return voltageReportIsReady;
//}

//bool MainBoardWidget::checkReportStage(unsigned int commandId)
//{
//    if (commandId == commandGETVOLTAGES) {

//        //check first whether the System is perfroming I2C Scan:
//        if (i2cScanIsPerfroming) {
//            voltageReportIsReady = false;
//            qDebug() << "I2C Scan is perfroming! Restricted!";
//            return false; //restrict to send the command;

//        }

//        //check if the programm is waiting for uC System to answer
//        if ((!getVoltageReportIsReady()) && (getIsWatingForReport())) {
//            waitForReportTimer = new QTimer(this);
//            waitForReportTimer->setSingleShot(true);
//            waitForReportTimer->start(waitFORVOLTAGECURRENTREPORT); //1 second default
//            while (waitForReportTimer->isActive()) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(10));
//                QApplication::processEvents();
//                if (getVoltageReportIsReady()) {
//                    waitForReportTimer->stop();
//                    voltageReportIsReady = false;
//                    return true; //let go further
//                }
//            }
//            voltageReportIsReady = false;
//            qDebug() << "No VoltageCurrent report has come! ";
//            return false;


//        }
//        else {
//            voltageReportIsReady = false;
//            return true;
//        }
//    }
//    if (commandId == commandPERFORMI2CSCAN) {
//       //check if the programm is waiting for uC System to answer
//        //disable other scans..
//        voltageReportIsReady = false;

//        if ((!getI2cReportIsReady()) && (getIsWatingForReport())) {
//            waitForReportTimer = new QTimer(this);
//            waitForReportTimer->setSingleShot(true);
//            waitForReportTimer->start(2000); //4 seconds default
//            while (waitForReportTimer->isActive()) {
//                std::this_thread::sleep_for(std::chrono::milliseconds(500));
//                QApplication::processEvents();
//                if (getI2cReportIsReady()) {
//                    waitForReportTimer->stop();
//                    i2cReportIsReady = false;
//                    return true; //let go further
//                }
//            }
//            i2cReportIsReady = false;
//            qDebug() << "No I2C report has come! ";
//            return false;


//        }
//        else {
//            i2cReportIsReady = false;
//            return true;
//        }

//    }



//    return true;
//}



void MainBoardWidget::setB731Commands()
{

}

void MainBoardWidget::setSipSapphireCommands()
{


    //vector


    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportBoardInfo","_getBoardInfo\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportVoltagesCurrents","_getVoltages\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportTemperature","_getTemperature\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportI2CScanResults","_performI2CScan\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportBoardReseted","_boardReset\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportCryptoEngineReseted","_cryptoEngineReset\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportMainCPUReseted","_mainCpuReset\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportExtProgrEnabled","_enExtProgr\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportIntProgrEnabled","_enIntProgr\r"));
    _commandsSiPSapphireDevBoard.push_back(SipSapphireCommand("sysReportAutoLog","_enAutoLogs\r"));



}

void MainBoardWidget::openSerialPort()
{
    SettingsDialog::Settings p = _settings->settings();
    _mainCPUport->setPortName(p.name);
    _mainCPUport->setBaudRate(p.baudRate);
    _mainCPUport->setDataBits(p.dataBits);
    _mainCPUport->setParity(p.parity);
    _mainCPUport->setStopBits(p.stopBits);
    _mainCPUport->setFlowControl(p.flowControl);
    if (_mainCPUport->open(QIODevice::ReadWrite)) {
        ui->logsMainProcessor->setEnabled(true);
        ui->logsMainProcessor->setLocalEchoEnabled(p.localEchoEnabled);


    }
    //NO DEBUG FOR A WHILE!!!!

}

void MainBoardWidget::closeSerialPort()
{
    if (_mainCPUport->isOpen()) _mainCPUport->close();
    ui->logsMainProcessor->setEnabled(false);


}

void MainBoardWidget::sendCommand(unsigned int commandId)
{
    if (_mainCPUport->isWritable()) {


        if (isWatingForReport) {
            qDebug() << "Device is not ready!";
            //here to start the timer and wait for setted time of waiting for each type of scan;



            return;
        }
        else {

            //here to set that the System is Waiting...
            if (commandId == commandPERFORMI2CSCAN) {
                i2cScanIsPerforming = true;
                waitForReportTimer->setInterval(waitFORI2CREPORT);
            }
            else if (commandId == commandGETVOLTAGES) {

                voltageCurrentScanIsPerforming = true;
                waitForReportTimer->setInterval(waitFORVOLTAGECURRENTREPORT);

            }

            //set the TimeouTimer Interval:



            for (int var = 0; var < _commandsSiPSapphireDevBoard[commandId].command().length(); ++var) {

                char currSymbol = _commandsSiPSapphireDevBoard[commandId].command().toStdString().c_str()[var];
                QByteArray symbolArray(&currSymbol);
                symbolArray.truncate(1);
                //the trouble of sending the data is caused of synchronization.
                //If I have the debug point on the emit signal
                //everything is going perfect.
                waitms(11); //adjust this value to work stable...
                //ADjusted value for 115200 baudRate is 11 ms. If
                _mainCPUport->waitForBytesWritten(-1);


                emit ui->logsMainProcessor->getData(symbolArray);


                //qDebug() << "Symbol sent to port: " << symbolArray;
            }
            setIsWatingForReport(true); //set that the programm is waiting for report;
            //start the timer;
            waitForReportTimer->start();


        }

     }


}

//bool MainBoardWidget::checkReportStatus()
//{
//    return getVoltageReportIsReady();
//}



void MainBoardWidget::writeData(const QByteArray &data)
{
    long long error = _mainCPUport->write(data);
    _mainCPUport->waitForBytesWritten(-1);
    //qDebug() << "Number of Bytes to send: " << error;
    //qDebug() << "Data to send: " << data;
}

void MainBoardWidget::readData()
{
    QByteArray data = _mainCPUport->readAll();
    QString reportData(data);
    ui->logsMainProcessor->putData(data);
    if (ucReportsReceiver(reportData)) ucReportsParser();
}

void MainBoardWidget::resetTheWaitingState()
{
    if (isWatingForReport) {
        if (i2cScanIsPerforming) {
            i2cScanIsPerforming = false;
            qDebug() << "i2c Scan has failed! Please, check the connection.";
        }
        else if (voltageCurrentScanIsPerforming) {

            voltageCurrentScanIsPerforming = false;
            qDebug() << "voltages Scan has failed! Please, check the connection!";

    }
        isWatingForReport = false;
    }
}

void MainBoardWidget::stopTheWaitforReportTimer()
{
    qDebug() << "Report has come in time. Time left: "<< waitForReportTimer->remainingTime();
    waitForReportTimer->stop();


}




