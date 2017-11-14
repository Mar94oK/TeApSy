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

private:
    Ui::MainBoardWidget *ui;

    QSize _mainWindowSize;

    //to receive it from parsing the table;
    QString _mainBoardWidgetPicturePath;

    //QSerial Ports
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



private slots:

    void openSerialPort();
    void closeSerialPort();

    void writeData(const QByteArray &data);
    void readData();



public slots:

    void sendCommand(unsigned int commandId);
    //void readData();

signals:

    void voltageCurrentDataIsReady(std::vector<VoltageCurrentData>);


};

#endif // MAINBOARDWIDGET_H
