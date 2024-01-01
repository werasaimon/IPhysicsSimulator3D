#ifndef TRIPODEDYNAMIC_H
#define TRIPODEDYNAMIC_H

#include "TripodeHardware.h"
#include "glwidget.h"
#include <ActuatorDynamic.h>
#include <HingeMountTwoAxis.h>
#include <Sensors/ISensors.hpp>
#include <TripodeHardware.h>



class TripodeDynamic : public OpenGL_Render_Interface , public TripodeHardware
{
public:

    TripodeDynamic(GLWidget *_globalScene_);

    void Draw();
    void Shot();

    IOrientationSensor *GetOrientationSensor() const;



private :

//    float m_PositionActuator1;
//    float m_PositionActuator2;

//    float m_Yaw;
//    float m_Pitch;

//    float m_PrevYaw;
//    float m_PrevPitch;

//    IOrientationSensor *m_OrientationSensor;
//    Quaternion m_InitBasis;

    //---------------------------//

//    ActuatorDynamic *m_Actuator1;
//    ActuatorDynamic *m_Actuator2;

    HingeMountTwoAxis *m_Hinge0;

    HingeMountTwoAxis *m_Hinge1;
    HingeMountTwoAxis *m_Hinge2;

    HingeMountTwoAxis *m_Hinge3;
    HingeMountTwoAxis *m_Hinge4;

    Vector3 pos_A;
    Vector3 pos_B;
    Vector3 pos_C;
    Vector3 point_forward;


    IComponentRigidBody *RigidBody_Fixola_1;
    IComponentRigidBody *RigidBody_Fixola_2;

    IComponentRigidBody *RigidBody_VisionModul;
    IComponentRigidBody *RigidBody_Forward;

    IComponentRigidBody *RigidBody_Fixed;

    //---------------------------//

    IComponentRigidBody *RigidBody_Gun;

    //---------------------------//

};

#endif // TRIPODEDYNAMIC_H
