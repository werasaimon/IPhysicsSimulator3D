#ifndef CHART_WIDGET_H
#define CHART_WIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QMap>

// Класс Chart_Widget наследуется от QChartView и представляет собой виджет для отображения графиков.
class Chart_Widget : public QChartView
{
    Q_OBJECT // Макрос Q_OBJECT необходим для работы механизма сигналов и слотов Qt.

public:
    // Конструктор класса, принимает родительский виджет в качестве параметра.
    Chart_Widget(QWidget *parent = nullptr);

    // Метод для вывода текста в консоль отладки.
    void setText(QString str)
    {
        qDebug() << str;
    }

    QChart *Chart() const;

    // Метод для добавления серии данных на график.
    void addSeries(QString name, QLineSeries* series);

    // Метод для управления видимостью серии данных на графике.
    void setSeriesVisibility(QString name, bool isVisible);

    // Метод для удаления всех серий данных с графика.
    void clearAllSeries();

    // Метод для полной очистки графика.
    void clearChart();

    void Focus();

    // Метод для получения серии данных по ее имени.
    QLineSeries* getSeries(QString name);

    void setMax_plot_length(uint16_t newMax_plot_length);

public:

    // Максимальная длина графика.
    uint16_t max_plot_length;

    // Указатель на объект QChart, который представляет сам график.
    QChart *m_Chart;

    // Карта, связывающая имена серий данных и указатели на эти серии.
    QMap<QString, QLineSeries*> m_Series;


};

#endif // CHART_WIDGET_H
