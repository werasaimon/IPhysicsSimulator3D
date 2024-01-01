#ifndef IORIENTATIONSENSOR_H
#define IORIENTATIONSENSOR_H

#include "imaths.hpp"
#include <IEngineComponent/IComponents.hpp>

using namespace IEngine;
using namespace IMath;


class IOrientationSensor
{
public:


    IOrientationSensor(IComponentRigidBody *_PhysicsBody=nullptr , scalar _time_step=1.0)
        : m_PhysicsBody(_PhysicsBody) ,
          m_TimeStep(_time_step)
    {
        assert(m_PhysicsBody);
    }


    void setTimeStep(const scalar &TimeStep);

    Quaternion getQuaternion() const;
    Vector3 getAngle() const;

    Quaternion Orientation() const;
    scalar BarometricAltitude(const Vector3& _gravity) const;

    Vector3 AccelerometerAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const;
    Vector3 GyroscopeAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const;


private:

    IComponentRigidBody *m_PhysicsBody;
    scalar               m_TimeStep;


};



class IOrientationSensorLite
{

    Quaternion m_Quaternion;
    Vector3 m_EulerAngle;


public:

    IOrientationSensorLite()
    {

    }


    void setQuat(const Quaternion& _Quaternion)
    {
        m_Quaternion = _Quaternion;
    }

    void Update()
    {
        //m_EulerAngle = m_Quat.GetEulerAngles2();//
        m_EulerAngle = m_Quaternion.GetEulerAngleGimbalLock(Quaternion::RotSeq::yxz);
            //m_EulerAngle = m_Quat.GetEulerAngles();

        //        if (m_EulerAngle.y >= M_PI)
        //        {
        //           m_EulerAngle.y -= M_PI * 2.f;
        //        }
        //        else if (m_EulerAngle.y < -M_PI)
        //        {
        //           m_EulerAngle.y += M_PI * 2.f;
        //        }I
    }


    //    void Update2()
    //    {
    //        //m_EulerAngle = m_Quat.GetEulerAngles2();//
    //        m_EulerAngle = m_Quat.GetEulerAngleGimbalLock(Quaternion::RotSeq::zyz);
    //    }


    const Vector3 &EulerAngle() const
    {
        return m_EulerAngle;
    }
};



#endif // IORIENTATIONSENSOR_H
