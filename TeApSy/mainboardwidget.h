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

private slots:

    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();



};

#endif // MAINBOARDWIDGET_H
