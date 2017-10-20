#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QDialog>

namespace Ui {
class StartDialog;
}

class StartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StartDialog(QWidget *parent = 0);
    ~StartDialog();

private:
    Ui::StartDialog *ui;


signals:
    void showMainWindow(bool);
    void closeTheProgramm(bool);


public slots:
    void btnOKisPressed();
    void btnCancelIsPressed();




};

#endif // STARTDIALOG_H
