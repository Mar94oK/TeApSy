#ifndef TEMPHUMIDWIDGET_H
#define TEMPHUMIDWIDGET_H

#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/qchartview.h>
#include <QtCharts/QChart>
#include <QList>
#include <QString>
#include <sipsapphirerefboard.h>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QTime>

#define maximumPointsDisplayedTemperature 10 //please, allways set %10
#define maximumPointsDisplayedHumidity 10



QT_CHARTS_USE_NAMESPACE

typedef QPair<QPointF, QString> GraphData;
typedef QList<GraphData> DataList;
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
    QChart *createHumidityChart();
    QChart *createTemperatureChart();

private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    QLineSeries* seriesHumid;
    QLineSeries* seriesTemp;

    QValueAxis *_axisHumidityX;
    QValueAxis *_axisTemperatureX;
    QValueAxis *_axisHumidityY;
    QValueAxis *_axisTemperatureY;

private slots:

    void updateUI();

public:

    void updateTempGraph(TempHumidData*);
    void updateHumidGraph(TempHumidData*);



};

#endif // TEMPHUMIDWIDGET_H
