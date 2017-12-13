#ifndef MAINBOARDWIDGET_H
#define MAINBOARDWIDGET_H

#include <QWidget>
#include <QSize>
#include <QDesktopWidget>
#include <QRect>
#include <QImage>
#include <QPalette>
#include <QBrush>
#include <QString>
#include <QFile>
#include <QImage>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <settingsdialog.h>
#include <QtCore/QtGlobal>
#include <console.h>
#include <QMainWindow>
#include <QByteArray>
#include <QString>
#include <vector>
#include <sipsapphirerefboard.h>
#include <QFile>
#include <QStringList>
#include <QList>
#include <console.h>
#include <QTimer>
#include <chrono>
#include <thread>


//in order they are added in the void MainBoardWidget::setSipSapphireCommands() method
#define commandGETBOARDINFO 0
#define commandGETVOLTAGES 1
#define commandGETTEMPERATURE 2
#define commandPERFORMI2CSCAN 3
#define commandBOARDRESET 5
#define commandCRYPTOENGINERESET 6
#define commandMAINCPURESET 7
#define commandENEXTPROGR 8
#define commandENINTPROGR 9
#define commandENAUTOLOGS 10


#define waitFORVOLTAGECURRENTREPORT 1000 //maximum of 1 second
#define waitFORI2CREPORT 4000 //maximum of 4 seconds
#define waitFORHUMIDTEMPREPORT 1000 //maximum of 1 second










class Console;
class SettingsDialog;







namespace Ui {
class MainBoardWidget;
}

class MainBoardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainBoardWidget(QWidget *parent = 0);
    ~MainBoardWidget();

    QSize mainWindowSize() const;
    void setMainWindowSize(const QSize &mainWindowSize);


    void setMainBoardWidgetPicturePath(const QString &picturePath);

    //this methods should be allways called in the constructor
    void setSipSapphireCommands();
    void setB731Commands();

    //bool getVoltageReportIsReady() const;

    //bool checkReportStage(unsigned int commandId);

    bool getIsWatingForReport() const;
    void setIsWatingForReport(bool value);

    //bool getI2cReportIsReady() const;

private:
    Ui::MainBoardWidget *ui;

    QSize _mainWindowSize;

    //to receive it from parsing the table;
    QString _mainBoardWidgetPicturePath;

    //QSerial Ports
    QSerialPort* _uClogsPort;
    QSerialPort* _mainCPUport;
    QSerialPort* _cryptoEnginePort;

    //Settings Dialogs;
    SettingsDialog* _settings;
    //Console* _console; //they are present in the Designer;

    void initActionsConnections();


    std::vector<SipSapphireCommand> _commandsSiPSapphireDevBoard;


    bool ucReportsReceiver(QString reportData);
    void ucReportsParser();

    std::vector<QString> _reportsData; //stores the current report data;
    QString _ucReportsData;
    std::vector<VoltageCurrentData> _voltageCurrentData;

    TempHumidData _tempHumidData;



    //bool i2cReportIsReady = false;
    //bool voltageReportIsReady = false;

    bool isWatingForReport = false;



    bool i2cScanIsPerforming = false;
    bool voltageCurrentScanIsPerforming = false;
    bool humidityTemperatureMeasurementIsPerforming = false;


    QTimer* waitForReportTimer;



private slots:

    void openSerialPort();
    void closeSerialPort();

    void writeData(const QByteArray &data);
    void readData();

    void resetTheWaitingState();
    void stopTheWaitforReportTimer();




public slots:

    void sendCommand(unsigned int commandId);
    //bool checkReportStatus();



signals:

    void voltageCurrentDataIsReady(std::vector<VoltageCurrentData>);
    void i2cDeviceDataIsReady(std::vector<I2CDevice>);
    void signal_stopTheWaitForReportTimer();
    void tempHumidDataIsReady(TempHumidData*);


};

#endif // MAINBOARDWIDGET_H
