#include "temphumidwidget.h"
#include "ui_temphumidwidget.h"

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



TempHumidWidget::TempHumidWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TempHumidWidget), m_listCount(1),
    m_valueMax(1),
    m_valueCount(1),
    m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))

{
    ui->setupUi(this);

    //connectSignals();
    QChartView *chartView;

    chartView = new QChartView(createHumidityChart());
    ui->lt_Graphics->addWidget(chartView);
    chartView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_charts << chartView;

    chartView = new QChartView(createTemperatureChart());
    ui->lt_Graphics->addWidget(chartView);
    chartView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    m_charts << chartView;

    updateUI();


}

TempHumidWidget::~TempHumidWidget()
{
    delete ui;
}

DataTable TempHumidWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;

    // set seed for random stuff
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    // generate random data
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << GraphData(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

//QLineSeries* seriesHumid;
//QLineSeries* seriesTemp;

QChart *TempHumidWidget::createHumidityChart()
{
    QChart* chart = new QChart();
    chart->setTitle("Humidity state");
    QString name("Humidity ");

    int nameIndex = 0;
    foreach ( DataList list, m_dataTable) {
        seriesHumid = new QLineSeries(chart);
        foreach (GraphData data, list)
        seriesHumid->append(data.first);
        seriesHumid->setName((name + QString::number(nameIndex)));
        nameIndex++;
        chart->addSeries(seriesHumid);
    }
    chart->createDefaultAxes();
    return chart;
}

QChart *TempHumidWidget::createTemperatureChart()
{
    QChart* chart = new QChart();
    chart->setTitle("Temperature state");
    QString name("Temperature ");

    int nameIndex = 0;
    foreach ( DataList list, m_dataTable) {
        seriesTemp = new QLineSeries(chart);
        foreach (GraphData data, list)
        seriesTemp->append(data.first);
        seriesTemp->setName((name + QString::number(nameIndex)));
        nameIndex++;
        chart->addSeries(seriesTemp);
    }
    chart->createDefaultAxes();

    return chart;
}

void TempHumidWidget::updateUI()
{
    QChart::ChartTheme theme = QChart::ChartThemeBlueCerulean;
    //QChart::ChartTheme theme = QChart::ChartThemeQt;

    foreach (QChartView *chartView, m_charts)
        chartView->chart()->setTheme(theme);
    QPalette pal = window()->palette();
    pal.setColor(QPalette::Window, QRgb(0x40434a));
    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
    window()->setPalette(pal);
    foreach (QChartView *chart, m_charts)
        chart->setRenderHint(QPainter::Antialiasing, true);

    Qt::Alignment alignment = Qt::AlignBottom;
    if (!alignment) {
        foreach (QChartView *chartView, m_charts)
            chartView->chart()->legend()->hide();
    } else {
        foreach (QChartView *chartView, m_charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }

}

void TempHumidWidget::updateTempGraph(TempHumidData data)
{
    seriesTemp->append(data._temperatureData.size(), static_cast<double>(data._temperatureData.back()));
}

void TempHumidWidget::updateHumidGraph(TempHumidData data)
{
    seriesHumid->append(data._humidityData.size(), static_cast<double>(data._humidityData.back()));
}
