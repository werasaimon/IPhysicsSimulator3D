#ifndef GLWIDGET_TUREL_H
#define GLWIDGET_TUREL_H


#include <QObject>
#include "glwidget.h"
#include "TripodeDynamic.h"


struct alignas(16) InterfaceCommunication
{
    InterfaceCommunication(int _a = 0, int _b = 0, int _c = 0,
                           int _d = 0, int _e = 0, int _f = 0 ,
                           int _buttonState = 0)
        : a(_a), b(_b), c(_c),
          d(_d), e(_e), f(_f),
          buttonState(_buttonState)
    {
    }

    int16_t a;
    int16_t b;
    int16_t c;
    int16_t d;
    int16_t e;
    int16_t f;
    int16_t buttonState;
};


class GLWidget_Turel : public GLWidget
{

    Q_OBJECT

public:

    explicit GLWidget_Turel(QWidget *parent = nullptr);
    ~GLWidget_Turel();

    virtual void initializeGL();
    virtual void update_scene();
    virtual void paintGL();


    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);


    bool is_stabilizaton = false;
    Vector3 control_angle;
    TripodeDynamic* m_TripodDynamics;

private:

};

#endif // GLWIDGET_TUREL_H
