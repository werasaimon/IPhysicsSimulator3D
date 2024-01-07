#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <SDL2/SDL.h>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QAreaSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

     MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

     void keyPressEvent( QKeyEvent *keyEvent);
     void keyReleaseEvent( QKeyEvent *keyEvent);

 private slots:

     void update_timer();

     void on_pushButton_Simulate_clicked();

 private:

     Ui::MainWindow *ui;

     //-----------------------//
     QTimer *mTimer; float time=0;
     //-----------------------//

};
#endif // MAINWINDOW_H
