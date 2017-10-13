#ifndef THELOADERWINDOW_H
#define THELOADERWINDOW_H

#include <QMainWindow>
#include <QTimer>

#define STARTUP_TIME_LOADER 3000 //defines the time that Loader Window Is Ative

namespace Ui {
class TheLoaderWindow;
}

class TheLoaderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TheLoaderWindow(QWidget *parent = 0);
    ~TheLoaderWindow();

private:
    Ui::TheLoaderWindow *ui;
    QTimer* _startUpTimer;


signals:

    void startUpletsGo(bool);


public slots:

    void startUpTimerEndCount(void);


};

#endif // THELOADERWINDOW_H
