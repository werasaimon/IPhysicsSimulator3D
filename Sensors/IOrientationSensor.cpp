#include "IOrientationSensor.h"
#include "imaths.hpp"


void IOrientationSensor::setTimeStep(const scalar &TimeStep)
{
    m_TimeStep = TimeStep;
}

Quaternion IOrientationSensor::getQuaternion() const
{
    return converAddaptive_Z(m_PhysicsBody->PhysRigidBody()->getTransform().getOrientation());
}

Vector3 IOrientationSensor::getAngle() const
{
    return getQuaternion().GetEulerAngleGimbalLock(Quaternion::RotSeq::zxy);
}

Quaternion IOrientationSensor::Orientation() const
{
    return m_PhysicsBody->GetTransform().GetRotation();
}

scalar IOrientationSensor::BarometricAltitude(const Vector3 &_gravity) const
{
    return m_PhysicsBody->GetTransform().GetPosition().Dot(_gravity);
}

Vector3 IOrientationSensor::AccelerometerAngle(const Quaternion &desired_correction_value_tau) const
{
    return  (m_PhysicsBody->GetTransform().GetRotation() * desired_correction_value_tau).GetEulerAngleGimbalLock();
}

Vector3 IOrientationSensor::GyroscopeAngle(const Quaternion &desired_correction_value_tau) const
{
    return (m_PhysicsBody->GetTransform().GetRotation() * desired_correction_value_tau) *
           m_PhysicsBody->GetAngularVelocity() * m_TimeStep;
}
