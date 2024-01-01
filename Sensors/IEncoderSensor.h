#ifndef IENCODERSENSOR_H
#define IENCODERSENSOR_H

#include <IEngineComponent/IComponents.hpp>

using namespace IEngine;
using namespace IMath;

class IEncoderSensor
{
public:
    IEncoderSensor(rp3d::HingeJoint *_HingeJoint, const Vector3& _normal = Vector3::Z)
        : m_Normal(_normal) ,
          m_HingeJoint(_HingeJoint)
    {

    }

    void Update(float _dt);
\
    scalar getPos() const;
    scalar getVel() const;

private:

    Vector3 m_Normal;
    rp3d::HingeJoint *m_HingeJoint;
    scalar pos;
    scalar vel;

};

#endif // IENCODERSENSOR_H
