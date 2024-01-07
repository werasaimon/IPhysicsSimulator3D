#include "IVirtualOrientationSensor.h"


Quaternion IVirtualOrientationSensor::Rotation() const
{
    return converAddaptive(m_PhysicsBody->getTransform()).GetRotation();
}

Vector3 IVirtualOrientationSensor::AccelerometerAngle(const Quaternion &desired_correction_value_tau) const
{
    return  (converAddaptive(m_PhysicsBody->getTransform()).GetRotation() *
            desired_correction_value_tau).GetEulerAngles2();
}

Vector3 IVirtualOrientationSensor::GyroscopeAngle(const Quaternion &desired_correction_value_tau) const
{
    return (converAddaptive(m_PhysicsBody->getTransform()).GetRotation() * desired_correction_value_tau) *
           converAddaptive(m_PhysicsBody->getAngularVelocity()) * m_TimeStep;
}

Vector3 IVirtualOrientationSensor::AngleEuler() const
{
    return Rotation().GetEulerAngles3();
}

scalar IVirtualOrientationSensor::BarometricAltitude() const
{
    return converAddaptive(m_PhysicsBody->getTransform()).GetPosition().Dot(Vector3::Y);
}
