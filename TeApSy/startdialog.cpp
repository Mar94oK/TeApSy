#include "startdialog.h"
#include "ui_startdialog.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    QObject::connect(this->ui->buttonBox, &QDialogButtonBox::accepted, this, &StartDialog::btnOKisPressed);
    QObject::connect(this->ui->buttonBox, &QDialogButtonBox::rejected, this, &StartDialog::btnCancelIsPressed);

}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::btnOKisPressed()
{
    emit showMainWindow(true);
}

void StartDialog::btnCancelIsPressed()
{
    emit closeTheProgramm(true);
}
