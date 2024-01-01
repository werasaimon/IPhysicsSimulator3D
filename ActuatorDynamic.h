#ifndef ACTUATORDYNAMIC_H
#define ACTUATORDYNAMIC_H

#include <IEngineComponent/IComponents.hpp>
#include <Sensors/ISensors.hpp>
#include <OpenGL_Render_Interface.h>
#include <ActuatorHardware.h>


class GLWidget;

class ActuatorDynamic : OpenGL_Render_Interface , public ActuatorHardware
{
public:

    ActuatorDynamic(const Vector3& point1 ,
                    const Vector3& point2 ,
                    GLWidget *_globalScene_,
                    float angle=20);

    void Initilization();
    void setVelocity(const scalar& _velocity_pwm);
    //void UpdatePID(const scalar& _pos);
    void SetPWM( float _pwm_vel );

    void SetTransform( const Transform& _transform );


    scalar getTranslation() const
    {
        return m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getTranslation();
    }


    scalar getReadEncoder() const
    {
        return m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getTranslation();
    }


    Vector3 getLocalDirection() const
    {
        return m_Direction;
    }

    Vector3 getWorldDirection() const
    {
        auto q = m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->getTransform().getOrientation();
        return (converAddaptive(q) * m_Direction).GetUnit();
    }


    Vector3 getColosetstPoint() const
    {
        return m_RigidBodyShtok2->GetTransform() * (getLocalDirection() * getLength() * scalar(0.5));
    }

    Vector3 getBottomPoint() const
    {
        return m_RigidBodyShtok1->GetTransform() * (getLocalDirection() * getLength() * scalar(-0.5));
    }


    scalar getLength() const
    {
        return m_Length;
    }

    //---------------------------------------//

    void Draw();

    //-----------------------------------------------------------//

    IComponentConstraitJoint *SliderConstraintJoint() const;
    IComponentRigidBody *RigidBody1();
    IComponentRigidBody *RigidBody2();

    IComponentRigidBody *BaseBody();
    IComponentRigidBody *ShtokBody();

    //-----------------------------------------------------------//

    Quaternion GetOrientDirection() const;

private:

    float m_Length;

    //float m_Position;
    float m_Velocity;
    //float m_CofficientPos;
    float m_CofficientVel;

    //float m_MaxVelocity;
    //float m_MinVelocity;

    Vector3 m_Direction;

    Vector3 m_Center1;
    Vector3 m_Center2;

    //-----------------------------------------------//

    IComponentConstraitJoint *m_SliderConstraintJoint;

    Vector3 m_Point1;
    Vector3 m_Point2;

    IComponentRigidBody *m_RigidBodyShtok1;
    IComponentRigidBody *m_RigidBodyShtok2;

    //-----------------------------------------------//

    Quaternion m_OrientDirection;
};

#endif // ACTUATORDYNAMIC_H
