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


    time = 0;
    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(update_timer()));

    //----------------------------------------------------//
    //joystick = JoystickInit(0);
    //----------------------------------------------------//


    // Initialize SDL
    if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }

    // Check if there are joysticks available
    if (SDL_NumJoysticks() < 1)
    {
        std::cerr << "No joysticks connected!" << std::endl;
    }

    // Open the first joystick
    joystick = SDL_JoystickOpen(0);
    if (!joystick)
    {
        std::cerr << "Unable to open joystick! SDL_Error: " << SDL_GetError() << std::endl;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    SDL_Quit();
}


SDL_Joystick* MainWindow::JoystickInit(int index_joystick)
{
    // Инициализация SDL для использования джойстика
    SDL_Init(SDL_INIT_JOYSTICK);
    // Включаем
    SDL_JoystickEventState(SDL_ENABLE);

    // If there are no joysticks connected, quit the program
    if (SDL_NumJoysticks() <= 0)
    {
        printf("There are no joysticks connected. Quitting now...\n");
        SDL_Quit();
    }

    // Open the joystick for reading and store its handle in the joy variable
    auto _joystick = SDL_JoystickOpen(index_joystick);

    //----------------------------------------------------//

    if (_joystick != NULL)
    {
        // Get information about the joystick
        name = SDL_JoystickName(_joystick);
        num_axes = SDL_JoystickNumAxes(_joystick);
        num_buttons = SDL_JoystickNumButtons(_joystick);
        num_hats = SDL_JoystickNumHats(_joystick);

        printf("Now reading from joystick '%s' with:\n"
               "%d axes\n"
               "%d buttons\n"
               "%d hats\n\n",
               name,
               num_axes,
               num_buttons,
               num_hats);

    }

    return _joystick;
}

void MainWindow::JoystickClose(SDL_Joystick* _joystick)
{
    SDL_JoystickClose(_joystick);
}


void MainWindow::handleJoystickEvent(SDL_Event &event)
{
    if (event.type == SDL_JOYAXISMOTION)
    {
        // Joystick axis motion
        std::cout << "Joystick " << static_cast<int>(event.jaxis.which)
                  << " Axis " << static_cast<int>(event.jaxis.axis)
                  << " Value " << static_cast<int>(event.jaxis.value) << std::endl;
    }
    else if (event.type == SDL_JOYBUTTONDOWN)
    {
        // Joystick button press
        std::cout << "Joystick " << static_cast<int>(event.jbutton.which)
                  << " Button " << static_cast<int>(event.jbutton.button) << " pressed" << std::endl;
    }
    else if (event.type == SDL_JOYBUTTONUP)
    {
        // Joystick button release
        std::cout << "Joystick " << static_cast<int>(event.jbutton.which)
                  << " Button " << static_cast<int>(event.jbutton.button) << " released" << std::endl;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *keyEvent)
{
    ui->label_opengl->keyPressEvent(keyEvent);
}

void MainWindow::keyReleaseEvent(QKeyEvent *keyEvent)
{
    ui->label_opengl->keyReleaseEvent(keyEvent);
}

void MainWindow::on_horizontalSlider_actuatorPWM_valueChanged(int value)
{
   // ui->label_opengl->m_TripodDynamics->SetYaw(  value / 100.f);
   // qDebug() << "_yaw_: " <<  ui->label_opengl->m_TripodDynamics->GetYaw();
}


void MainWindow::on_horizontalSlider_actuatorPWM_2_valueChanged(int value)
{
  //  ui->label_opengl->m_TripodDynamics->SetPitch( value / 100.f );
  //  qDebug() << "_pitch_ : "  <<  ui->label_opengl->m_TripodDynamics->GetPitch();
}


//qreal xx = 0;
void MainWindow::on_pushButton_clicked()
{
    //ui->label_plot->m_Series1->append(QPointF(xx+=3.1,sin(xx)*10));
    //series1->append(QPointF(rand()%1000,rand()%20));

    mTimer->start(100);
}



void MainWindow::on_stabilization_toggled(bool checked)
{
  // ui->label_opengl->is_stabilizaton =  checked;
}

void MainWindow::update_timer()
{

   // auto angle =  IMath::IRadiansToDegrees( ui->label_opengl->m_TripodDynamics->GetOrientationSensor()->getAngle() );
   // ui->label_plot->m_Series1->append(QPointF(time++,angle.x));
   // ui->label_plot->m_Series2->append(QPointF(time++,angle.y));
   // ui->label_plot->m_Series3->append(QPointF(time++,angle.z));

   // if(time >= ui->label_plot->max_plot_length)
   // {
   //     ui->label_plot->m_Series1->clear();
   //     ui->label_plot->m_Series2->clear();
   //     ui->label_plot->m_Series3->clear();
   //     time=0;
   // }

//   bool quit = false;
//   SDL_Event e;

//   if(SDL_PollEvent(&e) != 0)
//   {
//       if (e.type == SDL_QUIT)
//       {
//           quit = true;
//       }
//       else if (e.type == SDL_JOYAXISMOTION || e.type == SDL_JOYBUTTONDOWN || e.type == SDL_JOYBUTTONUP)
//       {
//          // handleJoystickEvent(e);
//       }
//   }

   // if (SDL_QuitRequested())
   // {
   //     mTimer->stop();
   // }

   // if(SDL_IsGameController(0))
   // {
   //     float size_diff = 4096;
   //     float size_ang  = 4096;

   //     float a = (SDL_JoystickGetAxis(joystick, 0) / 32768.f) * size_diff;
   //     float b =-(SDL_JoystickGetAxis(joystick, 1) / 32768.f) * size_diff;
   //     float c = (SDL_JoystickGetAxis(joystick, 3) / 32768.f) * size_ang;
   //     float d = (SDL_JoystickGetAxis(joystick, 4) / 32768.f) * size_ang;
   //     float e =  0;//SDL_JoystickGetButton(joystick, 6);
   //     float f =  0;//SDL_JoystickGetButton(joystick, 7);

   //     qDebug() << a << b << c << d << e << f;

   //     ui->horizontalSlider_Yaw->setValue( ui->horizontalSlider_Yaw->value() + a / 100.f );
   //     ui->horizontalSlider_Pitch->setValue( ui->horizontalSlider_Pitch->value() + b / 100.f );

   //     bool button_joystick_0 = SDL_JoystickGetButton(joystick, 4);
   //     bool button_joystick_1 = SDL_JoystickGetButton(joystick, 5);
   //     bool button_joystick_2 = SDL_JoystickGetButton(joystick, 6);
   //     bool button_joystick_3 = SDL_JoystickGetButton(joystick, 7);

   //     if(button_joystick_3 == true)
   //     {
   //         ui->label_opengl->m_TripodDynamics->Shot();
   //     }
   // }
}


void MainWindow::on_horizontalSlider_Yaw_valueChanged(int value)
{
   // ui->label_opengl->control_angle.SetY(value/50.f);
}


void MainWindow::on_horizontalSlider_Pitch_valueChanged(int value)
{
   // ui->label_opengl->control_angle.SetX(value/50.f);
}

