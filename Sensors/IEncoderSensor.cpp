#include "IEncoderSensor.h"



void IEncoderSensor::Update(float _dt)
{
    auto transform = m_HingeJoint->getBody2()->getTransform();
    auto velocity = transform.getOrientation() * m_HingeJoint->getBody2()->getAngularVelocity();
    auto axis = transform.getOrientation() * converAddaptive(m_Normal);
    vel = (velocity * _dt).dot(axis);
    pos += vel;
    pos = round(pos*10)/10;
}
