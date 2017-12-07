#ifndef TEMPHUMIDWIDGET_H
#define TEMPHUMIDWIDGET_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/qchartview.h>
#include <QtCharts/QChart>
#include <QList>
#include <QString>


QT_CHARTS_USE_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

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

private:

    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void connectSignals();
    QChart *createHumidityChart() const;
    QChart *createTemperatureChart() const;

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;


private slots:

    void updateUI();

public:




};

#endif // TEMPHUMIDWIDGET_H
