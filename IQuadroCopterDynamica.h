#ifndef IQUADROCOPTERDYNAMICA_H
#define IQUADROCOPTERDYNAMICA_H

#include <QObject>
#include <ActuatorDynamic.h>
#include <HingeMountTwoAxis.h>
#include <Sensors/ISensors.hpp>
#include "OpenGL_Render_Interface.h"

class IQuadroCopterDynamica : public OpenGL_Render_Interface
{
public:
    IQuadroCopterDynamica(GLWidget *_globalScene_);
    void Init(GLWidget *_globalScene_);
};

#endif // IQUADROCOPTERDYNAMICA_H
