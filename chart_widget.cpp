#include "chart_widget.h"

Chart_Widget::Chart_Widget(QWidget *parent) : QChartView(parent)
{
    setInteractive(true);
    setRubberBand(QChartView::RectangleRubberBand); // Используйте RectangleRubberBand для выбора данных
    setRenderHint(QPainter::Antialiasing);

    m_Chart = new QChart();
    m_Chart->setTheme(QChart::ChartThemeDark);
    m_Chart->setDropShadowEnabled(true);


    //---------------------------------------//

    // auto m_Series1 = new QLineSeries(this);
    // auto m_Series2 = new QLineSeries(this);
    // auto m_Series3 = new QLineSeries(this);

    // // m_Chart->addSeries(m_Series["Pitch"]);
    // // m_Chart->addSeries(m_Series["Yaw"]);
    // // m_Chart->addSeries(m_Series["Roll"]);

    // QPen pen1(Qt::red);
    // pen1.setWidth(2);
    // m_Series1->setPen(pen1);

    // QPen pen2(Qt::green);
    // pen2.setWidth(2);
    // m_Series2->setPen(pen2);

    // QPen pen3(Qt::blue);
    // pen3.setWidth(2);
    // m_Series3->setPen(pen3);

    // addSeries("Pitch" , m_Series1);
    // addSeries("Yaw"   , m_Series2);
    // addSeries("Roll"  , m_Series3);


    // m_Chart->createDefaultAxes();
    // m_Chart->axes(Qt::Horizontal).first()->setRange(0, max_plot_length = 2000);
    // m_Chart->axes(Qt::Vertical).first()->setRange(-180, 180);

    setChart(m_Chart);
}

void Chart_Widget::addSeries(QString name, QLineSeries *series)
{
    // Добавление серии к графику и сохранение ее в QMap m_Series
    m_Series[name] = series;
    m_Chart->addSeries(series);
}

QLineSeries* Chart_Widget::getSeries(QString name)
{
    // Возвращает указатель на серию по ее имени
    return m_Series.value(name, nullptr);
}

void Chart_Widget::setMax_plot_length(uint16_t newMax_plot_length)
{
    max_plot_length = newMax_plot_length;
}

QChart *Chart_Widget::Chart() const
{
    return m_Chart;
}

void Chart_Widget::setSeriesVisibility(QString name, bool isVisible)
{
    // Установка видимости серии по ее имени
    if (m_Series.contains(name))
    {
        m_Series[name]->setVisible(isVisible);
    }
}

void Chart_Widget::clearAllSeries()
{
    // Очистка всех серий графика
    for(auto series : m_Series.values())
    {
        series->clear(); // Очистка данных серии
    }
}

void Chart_Widget::clearChart()
{
    // Очистка графика и удаление всех серий
    for(auto series : m_Series.values())
    {
        m_Chart->removeSeries(series); // Удаление серии из графика
        delete series; // Освобождение памяти, занятой серией
    }

    m_Series.clear(); // Очистка QMap m_Series
}

void Chart_Widget::Focus()
{
    m_Chart->createDefaultAxes();
    m_Chart->axes(Qt::Horizontal).first()->setRange(0, max_plot_length);
    m_Chart->axes(Qt::Vertical).first()->setRange(-180, 180);
}
