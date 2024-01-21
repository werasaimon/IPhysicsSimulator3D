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

    auto m_Series1 = new QLineSeries(this);
    auto m_Series2 = new QLineSeries(this);
    auto m_Series3 = new QLineSeries(this);

    QPen pen1(Qt::red);
    pen1.setWidth(2);
    m_Series1->setPen(pen1);

    QPen pen2(Qt::green);
    pen2.setWidth(2);
    m_Series2->setPen(pen2);

    QPen pen3(Qt::blue);
    pen3.setWidth(2);
    m_Series3->setPen(pen3);

    ui->label_plot->addSeries("Pitch" , m_Series1);
    ui->label_plot->addSeries("Yaw"   , m_Series2);
    ui->label_plot->addSeries("Roll"  , m_Series3);

    //--------------------------------------------//

    ui->label_plot->addSeries("line_velocity_X" , new QLineSeries(this));
    ui->label_plot->addSeries("line_velocity_Y" , new QLineSeries(this));
    ui->label_plot->addSeries("line_velocity_Z" , new QLineSeries(this));

    ui->label_plot->getSeries("line_velocity_X")->setPen(QPen(Qt::cyan));
    ui->label_plot->getSeries("line_velocity_Y")->setPen(QPen(Qt::magenta));
    ui->label_plot->getSeries("line_velocity_Z")->setPen(QPen(Qt::yellow));

    //--------------------------------------------//

    ui->label_plot->addSeries("angular_velocity_X" , new QLineSeries(this));
    ui->label_plot->addSeries("angular_velocity_Y" , new QLineSeries(this));
    ui->label_plot->addSeries("angular_velocity_Z" , new QLineSeries(this));

    ui->label_plot->getSeries("angular_velocity_X")->setPen(QPen(Qt::darkGreen));
    ui->label_plot->getSeries("angular_velocity_Y")->setPen(QPen(Qt::darkRed));
    ui->label_plot->getSeries("angular_velocity_Z")->setPen(QPen(Qt::white));

    //--------------------------------------------//

    ui->label_plot->setMax_plot_length(2000);
    ui->label_plot->Focus();

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
        auto linear_velocity = ui->label_opengl->QuadroDynamica()->PhysicsBody_Base()->GetLinearVelocity();
        auto angular_velocity = ui->label_opengl->QuadroDynamica()->PhysicsBody_Base()->GetAngularVelocity();

        qDebug() << angle.x << angle.y << angle.z;

        ui->label_plot->getSeries("Pitch")->append(QPointF(time,angle.x));
        ui->label_plot->getSeries("Yaw")->append(QPointF(time,angle.z));
        ui->label_plot->getSeries("Roll")->append(QPointF(time,angle.y));

        ui->label_plot->getSeries("line_velocity_X")->append(QPointF(time,linear_velocity.x));
        ui->label_plot->getSeries("line_velocity_Y")->append(QPointF(time,linear_velocity.z));
        ui->label_plot->getSeries("line_velocity_Z")->append(QPointF(time,linear_velocity.y));

        ui->label_plot->getSeries("angular_velocity_X")->append(QPointF(time,angular_velocity.x));
        ui->label_plot->getSeries("angular_velocity_Y")->append(QPointF(time,angular_velocity.z));
        ui->label_plot->getSeries("angular_velocity_Z")->append(QPointF(time,angular_velocity.y));


        if(time >= ui->label_plot->max_plot_length)
        {
            ui->label_plot->clearAllSeries();
            time=0;
        }
        else
        {
            time++;
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
    ui->label_plot->Focus();
    time=0;
}

void MainWindow::on_checkBox_VelocityX_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("line_velocity_X",checked);
}

void MainWindow::on_checkBox_VelocityY_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("line_velocity_Y",checked);
}

void MainWindow::on_checkBox_VelocityZ_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("line_velocity_Z",checked);
}

void MainWindow::on_checkBox_AngularX_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("angular_velocity_X",checked);
}

void MainWindow::on_checkBox_AngularY_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("angular_velocity_Y",checked);
}

void MainWindow::on_checkBox_AngularZ_toggled(bool checked)
{
    ui->label_plot->setSeriesVisibility("angular_velocity_Z",checked);
}

