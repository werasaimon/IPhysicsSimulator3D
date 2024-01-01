#ifndef GLWIDGET_ACTUATOR_H
#define GLWIDGET_ACTUATOR_H

#include "glwidget.h"
#include <QObject>
#include "ActuatorDynamic.h"

class GLWidget_Actuator : public GLWidget
{    
    Q_OBJECT

public:
    explicit GLWidget_Actuator(QWidget *parent = nullptr);
    ~GLWidget_Actuator();

    virtual void initializeGL();
    virtual void update_scene();
    virtual void paintGL();

    float pos;

private:

    ActuatorDynamic* m_Actuator;

};

#endif // GLWIDGET_ACTUATOR_H
