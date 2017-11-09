#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>
#include <boardsdata.h>
#include <QDebug>
#include <QLabel>
#include <measuredvalues.h>




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

    unsigned int _boardSelectedByUser;
    std::vector<BoardsData>_boardsData;








public slots:
    void startTheDialog();
    void closeTheApp();
    void updateTheBoardsData();

signals:

    void closeTheApplication(bool);




};

#endif // MAINWINDOW_H
