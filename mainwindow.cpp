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

        ui->label_plot->m_Series1->append(QPointF(time++,angle.x));
        ui->label_plot->m_Series2->append(QPointF(time++,angle.y));
        ui->label_plot->m_Series3->append(QPointF(time++,angle.z));

        if(time >= ui->label_plot->max_plot_length)
        {
            ui->label_plot->m_Series1->clear();
            ui->label_plot->m_Series2->clear();
            ui->label_plot->m_Series3->clear();
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
          qDebug() << "Stop";

    }
    else
    {
       ui->label_opengl->start_simulate();
       ui->pushButton_Simulate->setText("simulate on");
       mTimer->start(100);
         qDebug() << "Start";
    }
}

