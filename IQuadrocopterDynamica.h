#ifndef IQUADROCOPTERDYNAMICA_H
#define IQUADROCOPTERDYNAMICA_H

#include <QObject>
#include <Sensors/ISensors.hpp>
#include "OpenGL_Render_Interface.h"


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

    Quaternion Rotation() const
    {
        return converAddaptive(m_PhysicsBody->getTransform()).GetRotation();
    }

    Vector3 AccelerometerAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const
    {
        return  (converAddaptive(m_PhysicsBody->getTransform()).GetRotation() *
                 desired_correction_value_tau).GetEulerAngles2();
    }

    Vector3 GyroscopeAngle( const Quaternion& desired_correction_value_tau = Quaternion::IDENTITY) const
    {
        return (converAddaptive(m_PhysicsBody->getTransform()).GetRotation() * desired_correction_value_tau) *
                converAddaptive(m_PhysicsBody->getAngularVelocity()) * m_TimeStep;
    }

    scalar BarometricAltitude() const
    {
        return converAddaptive(m_PhysicsBody->getTransform()).GetPosition().Dot(Vector3::Y);
    }

    void setTimeStep(const scalar &TimeStep)
    {
        m_TimeStep = TimeStep;
    }
};


class GLWidget;

class IQuadrocopterDynamica : public OpenGL_Render_Interface
{
public:

    IQuadrocopterDynamica(GLWidget *_globalScene_);

    void Init(GLWidget *_globalScene_);

    void RenderDebug();
    void UpdatePosition(const Vector3 &_PositionStability);
    void UpdateAngle(const Vector3 &_PositionStability);


    //--------------------------------------------------------------------------//


    // stabilization height
    void UpdateStabilizationHeight(Vector3& out_F , const scalar &_tau_height , scalar _time_step);

    // stabilization position
    void UpdateStabilizationPosition(Vector3 &out_Angle , const Vector3 &_tau_coords , scalar _time_step, bool is_rotate_plane=false);

    // stabilization angle orientation
    void UpdateStabilizationAngle(Vector3& stab_moment ,const Vector3 &_tau_angle , scalar _time_step);


    //--------------------------------------------------------------------------//

    void UpdateStabilizationFreeControl(float _time_step);
    void UpdateStabilizationControlHeight(scalar expected_height, float _time_step);
    void UpdateStabilizationControlPosition(const Vector3 &expected_coords, scalar _time_step);

    //--------------------------------------------------------------------------//

    IComponentRigidBody *PhysicsBody() const;

    void SetTauAngles(const Vector3 &TauAngles);
    Vector3 Forward() const;
    Vector3 Left() const;


private:

    Vector3 mDynamicPoints[4];
    IComponentRigidBody *mRigidBody_Base;
    IVirtualOrientationSensor *mSensor;

    //-------------------------------//

    Vector3    m_TauAngles;
    Vector3    m_TauPosition;

    scalar     m_W[4];
    scalar     m_Lenght;
    scalar     m_Power;

    scalar     m_AngleYaw;

    Vector3 m_Direction;
    Vector3 m_Forward;
    Vector3 m_Left;

};

#endif // IQUADROCOPTERDYNAMICA_H
