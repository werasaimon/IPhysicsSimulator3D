#ifndef IVIRTUALORIENTATIONSENSOR_H
#define IVIRTUALORIENTATIONSENSOR_H

#include "imaths.hpp"
#include <IEngineComponent/IComponents.hpp>

class IVirtualOrientationSensor
{
    scalar m_TimeStep;
    rp3d::RigidBody *m_PhysicsBody;

public:

    IVirtualOrientationSensor(rp3d::RigidBody *_PhysicsBody=nullptr , scalar _time_step=1.0)
      : m_TimeStep(_time_step) ,
        m_PhysicsBody(_PhysicsBody)
    {
        assert(m_PhysicsBody);
    }

    void setTimeStep(const scalar &TimeStep)
    {
        m_TimeStep = TimeStep;
    }

    Quaternion Rotation() const;

    Vector3 AccelerometerAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const;
    Vector3 GyroscopeAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const;
    Vector3 AngleEuler() const;

    scalar BarometricAltitude() const;


};


#endif // IVIRTUALORIENTATIONSENSOR_H
