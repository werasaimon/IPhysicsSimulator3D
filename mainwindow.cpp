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

}


