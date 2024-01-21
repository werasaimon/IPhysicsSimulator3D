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
     void on_horizontalSlider_V1_valueChanged(int value);
     void on_horizontalSlider_V2_valueChanged(int value);
     void on_doubleSpinBox_v1_editingFinished();

     void on_doubleSpinBox_V2_editingFinished();

     void on_checkBox_Pitch_toggled(bool checked);

     void on_checkBox_Yaw_toggled(bool checked);

     void on_checkBox_Roll_toggled(bool checked);

     void on_pushButton_ClearChart_clicked();
\
     void on_checkBox_VelocityY_toggled(bool checked);

     void on_checkBox_VelocityZ_toggled(bool checked);

     void on_checkBox_VelocityX_toggled(bool checked);

     void on_checkBox_AngularX_toggled(bool checked);

     void on_checkBox_AngularY_toggled(bool checked);

     void on_checkBox_AngularZ_toggled(bool checked);

 private:

     Ui::MainWindow *ui;

     //-----------------------//
     QTimer *mTimer; float time=0;
     //-----------------------//

};
#endif // MAINWINDOW_H
