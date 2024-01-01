#include "chart_widget.h"



Chart_Widget::Chart_Widget(QWidget *parent)
    : QWidget(parent)
{
    // Создаем QChart и устанавливаем данные
    m_Chart = new QChart();

    m_Series1 = new QLineSeries(this);
    m_Series2 = new QLineSeries(this);
    m_Series3 = new QLineSeries(this);

    m_Chart->addSeries(m_Series1);
    m_Chart->addSeries(m_Series2);
    m_Chart->addSeries(m_Series3);
    m_Chart->setTitle("axis angle-X-Y-Z rotate sensor");
    m_Chart->createDefaultAxes();
    m_Chart->axes(Qt::Horizontal).first()->setRange(0, max_plot_length=2000);
    m_Chart->axes(Qt::Vertical).first()->setRange(-45, 45);


    QPen pen1 = m_Series1->pen();
    pen1.setWidth(2);
    pen1.setBrush(QBrush("red")); // or just pen.setColor("red");
    m_Series1->setPen(pen1);


    QPen pen2 = m_Series2->pen();
    pen2.setWidth(2);
    pen2.setBrush(QBrush("green")); // or just pen.setColor("green");
    m_Series2->setPen(pen2);


    QPen pen3 = m_Series3->pen();
    pen3.setWidth(2);
    pen3.setBrush(QBrush("blue")); // or just pen.setColor("blue");
    m_Series3->setPen(pen3);


    // Создаем QChartView и устанавливаем QChart
    QChartView *chartView = new QChartView(m_Chart);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
}
