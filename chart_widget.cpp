#include "chart_widget.h"


Chart_Widget::Chart_Widget(QWidget *parent)
  : QChartView(parent)
{

  // Включаем интерактивность графика
  setInteractive(true);

  // Включаем возможность выбора данных
  setRubberBand(QChartView::RectangleRubberBand);

  this->setRenderHint(QPainter::Antialiasing);
  this->setRubberBand(QChartView::VerticalRubberBand);
  // Создаем QChart и устанавливаем данные
  m_Chart = new QChart();

  // Включаем антиалиасинг для сглаживания
  m_Chart->setTheme(QChart::ChartThemeDark);
  m_Chart->setDropShadowEnabled(true);

  // Создаем серии с именами в качестве ключей
  m_Series["Pitch"] = new QLineSeries(this);
  m_Series["Yaw"] = new QLineSeries(this);
  m_Series["Roll"] = new QLineSeries(this);

  // Добавляем серии в график
  m_Chart->addSeries(m_Series["Pitch"]);
  m_Chart->addSeries(m_Series["Yaw"]);
  m_Chart->addSeries(m_Series["Roll"]);

  m_Chart->createDefaultAxes();
  m_Chart->axes(Qt::Horizontal).first()->setRange(0, max_plot_length=2000);
  m_Chart->axes(Qt::Vertical).first()->setRange(-180, 180);

  QPen pen1 = m_Series["Pitch"]->pen();
  pen1.setWidth(2);
  pen1.setBrush(QBrush("red")); // or just pen.setColor("red");
  m_Series["Pitch"]->setPen(pen1);

  QPen pen2 = m_Series["Yaw"]->pen();
  pen2.setWidth(2);
  pen2.setBrush(QBrush("green")); // or just pen.setColor("green");
  m_Series["Yaw"]->setPen(pen2);

  QPen pen3 = m_Series["Roll"]->pen();
  pen3.setWidth(2);
  pen3.setBrush(QBrush("blue")); // or just pen.setColor("blue");
  m_Series["Roll"]->setPen(pen3);

  this->setChart(m_Chart);
}

void Chart_Widget::addSeries(QString name, QLineSeries *series)
{
    m_Series[name] = series;
    m_Chart->addSeries(series);
}

void Chart_Widget::setSeriesVisibility(QString name, bool isVisible)
{
    if (m_Series.contains(name))
    {
        m_Series[name]->setVisible(isVisible);
    }
}

void Chart_Widget::clearAllSeries()
{
    for( auto it : m_Series)
    {
        it->clear();
    }
}

void Chart_Widget::clearChart()
{
    // Удаляем все серии из графика
    for (auto &series : m_Series) {
        m_Chart->removeSeries(series);
        delete series; // Удаляем объект серии
    }

    // Очищаем QMap
    m_Series.clear();
}
