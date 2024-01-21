#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QMap>

class Chart_Widget : public QChartView
{
    Q_OBJECT

public:
    Chart_Widget(QWidget *parent = nullptr);

    void setText(QString str)
    {
        qDebug() << str;
    }

    void addSeries(QString name, QLineSeries* series);
    void setSeriesVisibility(QString name, bool isVisible);
    void clearAllSeries();
    void clearChart();

public:

    uint16_t max_plot_length;

    QChart *m_Chart;
    QMap<QString, QLineSeries*> m_Series;
};


#endif // CHART_WIDGET_H
