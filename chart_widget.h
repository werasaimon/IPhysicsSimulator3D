#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>

class Chart_Widget : public QChartView
{
    Q_OBJECT

public:
    Chart_Widget(QWidget *parent = nullptr);

    void setText(QString str)
    {
        qDebug() << str;
    }

// protected:
//     void wheelEvent(QWheelEvent *event) override
//     {
//         // Изменяем масштаб графика в зависимости от направления прокрутки колеса мыши
//         int delta = event->angleDelta().y();
//         if (delta > 0)
//             m_Chart->zoomIn();
//         else
//             m_Chart->zoomOut();

//         QChartView::wheelEvent(event);
//     }

//private:
public:

    uint16_t max_plot_length;

    QChart *m_Chart;
    QLineSeries* m_Series1;
    QLineSeries* m_Series2;
    QLineSeries* m_Series3;
};

#endif // CHART_WIDGET_H
