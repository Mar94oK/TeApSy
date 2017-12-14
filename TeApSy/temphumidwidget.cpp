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
    ui(new Ui::TempHumidWidget) // m_listCount(1),  m_valueMax(1),  m_valueCount(1),
    //m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount))

{
    ui->setupUi(this);

    //connectSignals();
//    QChartView *chartView;

//    chartView = new QChartView(createHumidityChart());
//    ui->lt_Graphics->addWidget(chartView);
//    chartView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
//    m_charts << chartView;

//    chartView = new QChartView(createTemperatureChart());
//    ui->lt_Graphics->addWidget(chartView);
//    chartView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
//    m_charts << chartView;

//    updateUI();

    _humidGraph = createHumidityGraph();
    _tempGraph = createTemperatureGraph();


}

TempHumidWidget::~TempHumidWidget()
{
    delete ui;
}

QwtPlot *TempHumidWidget::createHumidityGraph()
{

    QwtPlot* humidPlot = new QwtPlot(this);

    humidPlot->setTitle("Humidity, %");
    humidPlot->setCanvasBackground(Qt::white);

    humidPlot->setAxisTitle(QwtPlot::yLeft, "Humidity");
    //humidPlot->setAxisTitle(QwtPlot::xBottom, "Current Measure");

    humidPlot->insertLegend(new QwtLegend());

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::green, 2));
    grid->attach(humidPlot);

    ui->lt_Graphics->addWidget(humidPlot);

    _humidityValues = new QwtPlotCurve();
    _humidityValues->setTitle( "Humidity" );
    _humidityValues->setPen( Qt::blue, 1 ); // цвет и толщина кривой
    _humidityValues->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

    // Маркеры кривой
    // #include <qwt_symbol.h>
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    _humidityValues->setSymbol( symbol );

    humidPlot->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    return humidPlot;


}

QwtPlot *TempHumidWidget::createTemperatureGraph()
{
    QwtPlot* temperPlot = new QwtPlot(this);

    temperPlot->setTitle("Temperature, %");
    temperPlot->setCanvasBackground(Qt::white);

    temperPlot->setAxisTitle(QwtPlot::yLeft, "Temperature");
    //temperPlot->setAxisTitle(QwtPlot::xBottom, "Current Measure");

    temperPlot->insertLegend(new QwtLegend());

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen(Qt::green, 2));
    grid->attach(temperPlot);

    ui->lt_Graphics->addWidget(temperPlot);

    _temperatureValues = new QwtPlotCurve();

    _temperatureValues->setTitle( "Humidity" );
    _temperatureValues->setPen( Qt::blue, 1 ); // цвет и толщина кривой
    _temperatureValues->setRenderHint
            ( QwtPlotItem::RenderAntialiased, true ); // сглаживание

    // Маркеры кривой
    // #include <qwt_symbol.h>
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    _temperatureValues->setSymbol( symbol );

    temperPlot->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    return temperPlot;
}




//DataTable TempHumidWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
//{
//    DataTable dataTable;

//    // set seed for random stuff
//    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

//    // generate random data
//    for (int i(0); i < listCount; i++) {
//        DataList dataList;
//        qreal yValue(0);
//        for (int j(0); j < valueCount; j++) {
//            yValue = yValue + (qreal)(qrand() % valueMax) / (qreal) valueCount;
//            QPointF value((j + (qreal) rand() / (qreal) RAND_MAX) * ((qreal) m_valueMax / (qreal) valueCount),
//                          yValue);
//            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
//            dataList << GraphData(value, label);
//        }
//        dataTable << dataList;
//    }

//    DataTable dataTable_changed;
//    float yValue = 0;
//    float xValue = 0;
//    QPointF initialPoint(xValue, yValue);
//    QString label = "Slice " + QString::number(0) + QString::number(0);
//    DataList dataList;
//    dataList << GraphData(initialPoint, label);
//    dataTable_changed << dataList;

//    return dataTable_changed;
//}

//QLineSeries* seriesHumid;
//QLineSeries* seriesTemp;

//QChart *TempHumidWidget::createHumidityChart()
//{
//    QChart* chart = new QChart();
//    chart->setTitle("Humidity state");
//    QString name("Humidity ");
//    _axisHumidityX = new QValueAxis;
//    _axisHumidityY = new QValueAxis;


//    int nameIndex = 0;
//    foreach ( DataList list, m_dataTable) {
//        seriesHumid = new QLineSeries(chart);
//        foreach (GraphData data, list)
//        seriesHumid->append(data.first);
//        seriesHumid->setName((name + QString::number(nameIndex)));
//        nameIndex++;
//        chart->addSeries(seriesHumid);
//    }
//    //chart->axisX()->setRange(0,10);
//    //chart->axisY()->setRange(0,100);
//    chart->createDefaultAxes();
//    chart->setAxisX(_axisHumidityX, seriesHumid);
//    chart->setAxisY(_axisHumidityY, seriesHumid);
//    _axisHumidityX->setTickCount(maximumPointsDisplayedHumidity);
//    chart->axisX()->setRange(0, maximumPointsDisplayedHumidity);
//    chart->axisY()->setRange(0, 100);



//    return chart;
//}

//QChart *TempHumidWidget::createTemperatureChart()
//{
//    QChart* chart = new QChart();
//    chart->setTitle("Temperature state");
//    QString name("Temperature ");
//    _axisTemperatureX = new QValueAxis;
//    _axisTemperatureY = new QValueAxis;

//    int nameIndex = 0;
//    foreach ( DataList list, m_dataTable) {
//        seriesTemp = new QLineSeries(chart);
//        foreach (GraphData data, list)
//        seriesTemp->append(data.first);
//        seriesTemp->setName((name + QString::number(nameIndex)));
//        nameIndex++;
//        chart->addSeries(seriesTemp);
//    }
//    //chart->axisX()->setRange(0,10);
//    //chart->axisY()->setRange(0,100);
//    chart->createDefaultAxes();
//    chart->setAxisX(_axisTemperatureX, seriesTemp);
//    chart->setAxisY(_axisTemperatureY, seriesTemp);
//    _axisTemperatureX->setTickCount(maximumPointsDisplayedTemperature);
//    chart->axisX()->setRange(0, maximumPointsDisplayedTemperature);
//    chart->axisY()->setRange(0, 100);


//    return chart;
//}

//void TempHumidWidget::updateUI()
//{
//    QChart::ChartTheme theme = QChart::ChartThemeBlueCerulean;
//    //QChart::ChartTheme theme = QChart::ChartThemeQt;

//    foreach (QChartView *chartView, m_charts)
//        chartView->chart()->setTheme(theme);
//    QPalette pal = window()->palette();
//    pal.setColor(QPalette::Window, QRgb(0x40434a));
//    pal.setColor(QPalette::WindowText, QRgb(0xd6d6d6));
//    window()->setPalette(pal);
//    foreach (QChartView *chart, m_charts)
//        chart->setRenderHint(QPainter::Antialiasing, true);

//    Qt::Alignment alignment = Qt::AlignBottom;
//    if (!alignment) {
//        foreach (QChartView *chartView, m_charts)
//            chartView->chart()->legend()->hide();
//    } else {
//        foreach (QChartView *chartView, m_charts) {
//            chartView->chart()->legend()->setAlignment(alignment);
//            chartView->chart()->legend()->show();
//        }
//    }

//}

void TempHumidWidget::updateTempGraph(TempHumidData* data)
{

//    if ((data->_temperatureData.size() < maximumPointsDisplayedTemperature) ||
//        (data->_temperatureData.size() == maximumPointsDisplayedTemperature)) {

//        _axisTemperatureX->setRange(0, maximumPointsDisplayedTemperature);
//        auto result = std::minmax_element(data->_temperatureData.begin(), data->_temperatureData.end());
//        _axisTemperatureY->setRange(static_cast<double>(*result.first) -1, static_cast<double>(*result.second) + 1);

//    }
//    else if (data->_temperatureData.size() > maximumPointsDisplayedTemperature) {

//        _axisTemperatureX->setRange(data->_temperatureData.size() - maximumPointsDisplayedTemperature, data->_temperatureData.size());
//        auto resultRescaleY = std::minmax_element(data->_temperatureData.end() - maximumPointsDisplayedTemperature, data->_temperatureData.end());
//        _axisTemperatureY->setRange(static_cast<double>(*resultRescaleY.first) -1, static_cast<double>(*resultRescaleY.second) + 1);
//    }



//    //_axisTemperatureX->applyNiceNumbers();
//    _axisTemperatureX->setLabelFormat("%d");
//    //if (!(data->_temperatureData.size() % 50)) seriesTemp->clear();
//    seriesTemp->append(data->_temperatureData.size(), static_cast<double>(data->_temperatureData.back()));

//    if (data->_temperatureData.size() == 11) {

//        float saver = data->_temperatureData[10];
//        data->_temperatureData.clear();
//        seriesTemp->clear();
//        data->_temperatureData.push_back(saver);
//        seriesTemp->append(data->_temperatureData.size(), static_cast<double>(data->_temperatureData.back()));
//    }

    _pointsTemperature << QPointF(data->_temperatureData.size(),static_cast<double>(data->_temperatureData.back()));
    _temperatureValues->setSamples(_pointsTemperature);
    _temperatureValues->attach(_tempGraph);
    _tempGraph->replot();


}

void TempHumidWidget::updateHumidGraph(TempHumidData *data)
{
    //Fisrt, found the maximum and minimum value of the presented values;


//    if ((data->_humidityData.size() < maximumPointsDisplayedHumidity) ||
//        (data->_humidityData.size() == maximumPointsDisplayedHumidity)) {



//        _axisHumidityX->setRange(0, maximumPointsDisplayedHumidity);

//        auto result = std::minmax_element(data->_humidityData.begin(), data->_humidityData.end());
//        if ((_axisHumidityY->min() > static_cast<double>(*result.first)) || (_axisHumidityY->max() < static_cast<double>(*result.second) )) {
//            _axisHumidityY->setRange(static_cast<double>(*result.first) -1, static_cast<double>(*result.second) + 1);
//        }


//    }
//    else if (data->_humidityData.size() > maximumPointsDisplayedHumidity) {



//        _axisHumidityX->setRange(data->_humidityData.size() - maximumPointsDisplayedHumidity, data->_humidityData.size());

//        auto resultRescaleY = std::minmax_element(data->_humidityData.end() - maximumPointsDisplayedHumidity, data->_humidityData.end());

//        if ((_axisHumidityY->min() > static_cast<double>(*resultRescaleY.first)) || (_axisHumidityY->max() < static_cast<double>(*resultRescaleY.second) )) {

//        _axisHumidityY->setRange(static_cast<double>(*resultRescaleY.first) -1, static_cast<double>(*resultRescaleY.second) + 1);

//        }


//    }

//    //_axisHumidityX->applyNiceNumbers();
//    _axisHumidityX->setLabelFormat("%d");

//    seriesHumid->append(data->_humidityData.size(), static_cast<double>(data->_humidityData.back()));

    //set the qwt Graph..
    _pointsHumidity << QPointF(data->_humidityData.size(),static_cast<double>(data->_humidityData.back()));
    _humidityValues->setSamples(_pointsHumidity);
    _humidityValues->attach(_humidGraph);
    _humidGraph->replot();


}
