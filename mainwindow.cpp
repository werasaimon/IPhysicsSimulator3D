#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QLineSeries>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simulation Physics Quadrocopters");

    //----------------------------------------------------//

    time = 0;
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(update_timer()));

    //----------------------------------------------------//

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    ui->label_opengl->keyPressEvent(keyEvent);
    keyEvent->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
    ui->label_opengl->keyReleaseEvent(keyEvent);
    keyEvent->accept();
}


void MainWindow::update_timer()
{
    if(ui->label_opengl->CScene()->Descriptor().m_IsDynamics)
    {
        auto angle =  IMath::IRadiansToDegrees( ui->label_opengl->QuadroDynamica()->Sensor()->AngleEuler() );

        qDebug() << angle.x << angle.y << angle.z;

        ui->label_plot->m_Series["Pitch"]->append(QPointF(time,angle.x));
        ui->label_plot->m_Series["Yaw"]->append(QPointF(time,angle.z));
        ui->label_plot->m_Series["Roll"]->append(QPointF(time,angle.y));
        time++;

        if(time >= ui->label_plot->max_plot_length)
        {
          ui->label_plot->clearAllSeries();
          time=0;
        }
    }
}



void MainWindow::on_pushButton_Simulate_clicked()
{
    if(ui->label_opengl->is_simulate())
    {
        ui->label_opengl->stop_simulate();
        ui->pushButton_Simulate->setText("simulate off");
        mTimer->stop();
          qDebug() << "Stop Physics Simulate";

    }
    else
    {
       ui->label_opengl->start_simulate();
       ui->pushButton_Simulate->setText("simulate on");
       mTimer->start(100);
         qDebug() << "Start Physics Simulate";
    }
}


void MainWindow::on_horizontalSlider_V1_valueChanged(int value)
{
    ui->doubleSpinBox_v1->setValue(value / 100.f);
}


void MainWindow::on_horizontalSlider_V2_valueChanged(int value)
{
    ui->doubleSpinBox_V2->setValue(value / 100.f);
}


void MainWindow::on_doubleSpinBox_v1_editingFinished()
{
   ui->horizontalSlider_V1->setValue(ui->doubleSpinBox_v1->value() * 100.f);
}


void MainWindow::on_doubleSpinBox_V2_editingFinished()
{
   ui->horizontalSlider_V2->setValue(ui->doubleSpinBox_V2->value() * 100.f);
}


void MainWindow::on_checkBox_Pitch_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("Pitch",checked);
}


void MainWindow::on_checkBox_Yaw_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("Yaw",checked);
}


void MainWindow::on_checkBox_Roll_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("Roll",checked);
}


void MainWindow::on_pushButton_ClearChart_clicked()
{
    ui->label_plot->clearAllSeries();
    time=0;
}

