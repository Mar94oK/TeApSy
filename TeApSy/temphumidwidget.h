#ifndef TEMPHUMIDWIDGET_H
#define TEMPHUMIDWIDGET_H

#include <QWidget>

namespace Ui {
class TempHumidWidget;
}

class TempHumidWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TempHumidWidget(QWidget *parent = 0);
    ~TempHumidWidget();

private:
    Ui::TempHumidWidget *ui;
};

#endif // TEMPHUMIDWIDGET_H
