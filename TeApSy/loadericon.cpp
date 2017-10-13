#include "loadericon.h"
#include "ui_loadericon.h"

LoaderIcon::LoaderIcon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoaderIcon)
{
    ui->setupUi(this);
}

LoaderIcon::~LoaderIcon()
{
    delete ui;
}
