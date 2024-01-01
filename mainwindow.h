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

     SDL_Joystick *JoystickInit(int index_joystick);
     void JoystickClose(SDL_Joystick *joystick);


     // Function to handle joystick events
     void handleJoystickEvent(SDL_Event& event);

 private slots:

     void on_horizontalSlider_actuatorPWM_valueChanged(int value);
     void on_horizontalSlider_actuatorPWM_2_valueChanged(int value);
     void on_pushButton_clicked();

     void on_stabilization_toggled(bool checked);

     void update_timer();

     void on_horizontalSlider_Yaw_valueChanged(int value);

     void on_horizontalSlider_Pitch_valueChanged(int value);

 private:

     Ui::MainWindow *ui;

     //-----------------------//
     QTimer *mTimer; float time=0;
     //-----------------------//
     //-----------------------//
     SDL_Joystick *joystick;
     const char *name;
     int num_axes;
     int num_buttons;
     int num_hats;
     //-----------------------//
     bool mIsShot;
};
#endif // MAINWINDOW_H
