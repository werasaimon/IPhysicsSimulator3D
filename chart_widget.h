#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

class Chart_Widget : public QWidget
{
    Q_OBJECT

public:
    Chart_Widget(QWidget *parent = nullptr);



    void setText(QString str)
    {
        qDebug() << str;
    }

    uint16_t max_plot_length;

    QChart *m_Chart;
    QLineSeries* m_Series1;
    QLineSeries* m_Series2;
    QLineSeries* m_Series3;
};

#endif // CHART_WIDGET_H
