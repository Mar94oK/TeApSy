#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StartDialog* _startDialog;

public slots:
    void startTheDialog();
    void closeTheApp();

signals:

    void closeTheApplication(bool);




};

#endif // MAINWINDOW_H
