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
    QLabel* labelVoltage = new QLabel();
    QLabel* labelCurrent = new QLabel();
    QHBoxLayout* pairLayout = new QHBoxLayout();
    VoltageCurrentLabels newPairOfLabels;

    labelCurrent->setText("Current Value");
    labelVoltage->setText("Voltage Value");

    newPairOfLabels._lblCurrent = labelCurrent;
    newPairOfLabels._lblVoltage = labelVoltage;
    pairLayout->addWidget(newPairOfLabels._lblVoltage);
    pairLayout->addWidget(newPairOfLabels._lblCurrent);
    newPairOfLabels._hboxPairLayout = pairLayout;


    _voltageCurrentLabels.push_back(newPairOfLabels);
    ui->lt_PairsOfValues->addLayout(_voltageCurrentLabels.back()._hboxPairLayout);


}
