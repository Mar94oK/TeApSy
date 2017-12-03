#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <startdialog.h>
#include <boardsdata.h>
#include <QDebug>
#include <QLabel>
#include <measuredvalues.h>
#include <sipsapphirerefboard.h>
#include <QTableView>
#include "QStandardItemModel"
#include "QStandardItem"
#include "QAbstractTableModel"


class I2cRepresentationModel;


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

    I2cRepresentationModel* i2cTableModel;



public slots:
    void startTheDialog();
    void closeTheApp();
    void updateTheBoardsData();
    void updateVoltageCurrentData(std::vector<VoltageCurrentData> newdata);


signals:

    void closeTheApplication(bool);
    void signal_updateVoltageCurrentData(std::vector<VoltageCurrentData>);




};

#endif // MAINWINDOW_H
