#include "measuredvalues.h"
#include "ui_measuredvalues.h"

MeasuredValues::MeasuredValues(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasuredValues)
{
    ui->setupUi(this);
}

MeasuredValues::~MeasuredValues()
{
    delete ui;
}

void MeasuredValues::addPairsWidgets()
{
    //create pointers to the Labels;
    QLabel* labelName = new QLabel();
    QLabel* labelVoltage = new QLabel();
    QLabel* labelCurrent = new QLabel();

    QHBoxLayout* pairLayout = new QHBoxLayout();
    VoltageCurrentLabels newPairOfLabels;


    labelName->setText("Name");
    labelCurrent->setText("Current Value");
    labelVoltage->setText("Voltage Value");

    newPairOfLabels._name = labelName;
    newPairOfLabels._lblCurrent = labelCurrent;
    newPairOfLabels._lblVoltage = labelVoltage;
    pairLayout->addWidget(newPairOfLabels._name);
    pairLayout->addWidget(newPairOfLabels._lblVoltage);
    pairLayout->addWidget(newPairOfLabels._lblCurrent);
    newPairOfLabels._hboxPairLayout = pairLayout;


    _voltageCurrentLabels.push_back(newPairOfLabels);
    ui->lt_PairsOfValues->addLayout(_voltageCurrentLabels.back()._hboxPairLayout);


}

void MeasuredValues::updateValues(std::vector<VoltageCurrentData> newData)
{
    unsigned int totalValues = 0;
    newData.size() > _voltageCurrentLabels.size() ? totalValues =  _voltageCurrentLabels.size() : totalValues = newData.size();

    for (unsigned int var = 0; var < totalValues; ++var) {
        _voltageCurrentLabels[var]._name->setText(newData[var]._name);
        _voltageCurrentLabels[var]._lblVoltage->setText(QString::number(static_cast<double>(newData[var]._valueVoltage)));
        _voltageCurrentLabels[var]._lblCurrent->setText(QString::number(static_cast<double>(newData[var]._valueCurrent)));
    }
    qDebug() << "End of Setting Values!";

}
