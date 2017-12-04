#ifndef MEASUREDVALUES_H
#define MEASUREDVALUES_H

#include <QWidget>
#include <vector>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include "sipsapphirerefboard.h"
#include <QDebug>



struct VoltageCurrentLabels{

    QLayout*_hboxPairLayout;
    QLabel* _name;
    QLabel* _lblVoltage;
    QLabel* _lblCurrent;

};


//struct I2CData {
//    QString ackedDevice;
//};

namespace Ui {
class MeasuredValues;
}

class MeasuredValues : public QWidget
{
    Q_OBJECT

public:
    explicit MeasuredValues(QWidget *parent = 0);
    ~MeasuredValues();

    void addPairsWidgets();

private:
    Ui::MeasuredValues *ui;

    std::vector<VoltageCurrentLabels>_voltageCurrentLabels;
    //std::vector<I2CData>_i2cDevicesFoundOnBus;

public slots:

    void updateValues(std::vector <VoltageCurrentData> newData);
    //void updateAddresses( std::vector<I2CData> newAdressess);

};

#endif // MEASUREDVALUES_H
