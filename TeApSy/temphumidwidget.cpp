#include "temphumidwidget.h"
#include "ui_temphumidwidget.h"

TempHumidWidget::TempHumidWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempHumidWidget)
{
    ui->setupUi(this);
}

TempHumidWidget::~TempHumidWidget()
{
    delete ui;
}
