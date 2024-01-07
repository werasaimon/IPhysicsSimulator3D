#include "IQuadrocopterDynamica.h"
#include "glwidget.h"

IQuadrocopterDynamica::IQuadrocopterDynamica(GLWidget *_globalScene_)
    : mRigidBody_Base(nullptr)
{
    this->Init(_globalScene_);
}

void IQuadrocopterDynamica::Init(GLWidget *_globalScene_)
{
    auto _physics__world_ = _globalScene_->CPhysicsWorld();
    auto _physics__instruments_ = _globalScene_->CPhysInstrument();
    auto _scene_ = _globalScene_->CScene();

    //---------------------------------------------------------------------//

    Vector3 pos = Vector3(0,10,0);
    mDynamicPoints[0] = Vector3(-10, 0,-10) * 0.5f;
    mDynamicPoints[1] = Vector3( 10, 0,-10) * 0.5f;
    mDynamicPoints[2] = Vector3( 10, 0, 10) * 0.5f;
    mDynamicPoints[3] = Vector3(-10, 0, 10) * 0.5f;

    Vector3 extendet(10,1,10);
    Transform base_trans(pos);
    mRigidBody_Base = new IComponentRigidBody(base_trans,_physics__world_);
    auto  collider_base =mRigidBody_Base->AddCollider(_physics__instruments_->CCreateBoxShape(extendet));
    mRigidBody_Base->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    MeshGenerator::CuboidDescriptor desc_base(extendet);
    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    base_mesh->setCollider(collider_base);
    _scene_->AddComponent( base_mesh );

    //---------------------------------------------------------------------//

    mSensor = new IVirtualOrientationSensor(mRigidBody_Base->PhysRigidBody());

}

//========================================================================================================//

void IQuadrocopterDynamica::RenderDebug()
{
    draw_sphere(mRigidBody_Base->GetTransform() * mDynamicPoints[0] , 0.5f , Vector3(1,0,0));
    draw_sphere(mRigidBody_Base->GetTransform() * mDynamicPoints[1] , 0.5f , Vector3(0,1,0));
    draw_sphere(mRigidBody_Base->GetTransform() * mDynamicPoints[2] , 0.5f , Vector3(0,0,1));
    draw_sphere(mRigidBody_Base->GetTransform() * mDynamicPoints[3] , 0.5f , Vector3(1,1,0));


    Vector3 position = mRigidBody_Base->GetTransform().GetPosition();
    draw_sphere(position , 0.75f , Vector3(1,1,1));
}

void IQuadrocopterDynamica::UpdatePosition(const Vector3& _PositionStability)
{
    this->UpdateStabilizationControlPosition(_PositionStability,1.f/60.f);
}

void IQuadrocopterDynamica::UpdateAngle(const Vector3 &_angle)
{
   Vector3 stab_moment;
   UpdateStabilizationAngle(stab_moment,_angle,1.f/60.f);
}


//========================================================================================================//


void IQuadrocopterDynamica::UpdateStabilizationHeight(Vector3 &F, const scalar &_tau_height, scalar _time_step)
{
    //-----------------------------------------------------------------------//
    scalar transient_time = 1./3;
    scalar norma_time = 2.9;
    scalar coff_battervorta_c1 = IPow((norma_time * transient_time), scalar(2));
    scalar coff_battervorta_c2 = 10.0 * 1.41421 * (norma_time * transient_time);
    //-----------------------------------------------------------------------//


    Vector3 linear_vel = mRigidBody_Base->GetLinearVelocity();
    scalar  massa = mRigidBody_Base->GetMassa();
    scalar  gravity = 0;//30.f * _time_step;

    scalar barometric_altitude = mSensor->BarometricAltitude();

    Vector3 Axis = Vector3::Y;
    scalar thrustVector_F =   massa * (gravity +
                                     -coff_battervorta_c1 * (barometric_altitude - _tau_height) -
                                      coff_battervorta_c2 * (linear_vel.Dot(Axis) * _time_step));

    //    scalar pitch = mSensors.AccelerometerAngle().GetX();
    //    scalar roll  = mSensors.AccelerometerAngle().GetZ();

    m_Power = thrustVector_F;// * cos(pitch)*cos(roll);
    F = mSensor->Rotation() * Vector3::Y * m_Power;
}



void IQuadrocopterDynamica::UpdateStabilizationPosition(Vector3 &outAngle, const Vector3 &_tau_coords, scalar _time_step, bool is_rotate_plane)
{
    //-----------------------------------------------------------------------//

    scalar transient_time = 1./10.0;
    scalar norma_time = 2.9;
    scalar coff_battervorta_c1 = IPow((norma_time * transient_time), scalar(2));
    scalar coff_battervorta_c2 = 10.0 * 1.41421 * (norma_time * transient_time);

    //-----------------------------------------------------------------------//

    Quaternion Q=Quaternion::FromAngleAxis(Vector3::Y, mSensor->AccelerometerAngle().GetY());
    Q.Normalize();

    //-----------------------------------------------------------------------//

    Vector3 linear_vel  = mRigidBody_Base->GetLinearVelocity();
    Vector3 position    = mRigidBody_Base->GetTransform().GetPosition();
    m_Forward = -(Q * Vector3::Z).Normalized();
    m_Left = -(Q * Vector3::X).Normalized();

    //-----------------------------------------------------------------------//

    if(is_rotate_plane)
    {
        IPlane plane(Vector3::Y,position);
        m_Direction = (plane.ClosestPoint(_tau_coords - position));
        if(m_Direction.LengthSquare() > 10)
        {
            outAngle.y += Vector3::AngleSigned(m_Direction.Normalized(),m_Forward,Vector3::Y)/10;
        }
    }

    //---------------------------------------------//

    Vector3 Left  = -m_Left;
    Vector3 Front = -m_Forward;
    scalar accel_left = -coff_battervorta_c1 * ((position - _tau_coords).Dot(Left)) -
                         coff_battervorta_c2 * ((linear_vel.Dot(Left) * _time_step));

    scalar accel_front = -coff_battervorta_c1 * ((position - _tau_coords).Dot(Front)) -
                          coff_battervorta_c2 * ((linear_vel.Dot(Front) * _time_step));

    scalar  gravity = 1.;// + 30.f * _time_step;
    outAngle.z =  IAtan( accel_left  / gravity);
    outAngle.x = -IAtan( accel_front / gravity);

    //-------------------------- Clamping ---------------------------//
    outAngle.z = IClamp(outAngle.z,scalar(-M_PI*0.25),scalar(M_PI*0.25));
    outAngle.x = IClamp(outAngle.x,scalar(-M_PI*0.25),scalar(M_PI*0.25));

}

void IQuadrocopterDynamica::UpdateStabilizationAngle(Vector3 &stab_moment, const Vector3 &_tau_angle, scalar _time_step)
{
    //-----------------------------------------------------------------------//

    scalar transient_time = 1.0/10;
    scalar norma_time = 2.9;
    scalar coff_battervorta_c1 = ((norma_time * transient_time) * (norma_time * transient_time));
    scalar coff_battervorta_c2 = 1.41421 * (norma_time * transient_time);

    //-----------------------------------------------------------------------//

    Quaternion  Q_Tau =
        Quaternion::FromAngleAxis(Vector3::X,_tau_angle.x) *
        Quaternion::FromAngleAxis(Vector3::Z,_tau_angle.z) *
        Quaternion::FromAngleAxis(Vector3::Y,_tau_angle.y);

    //-----------------------------------------------------------------------//

    mSensor->setTimeStep(_time_step);
    Vector3 accelerometer_angular_orientation_tau = mSensor->AccelerometerAngle(Q_Tau);
    Vector3 gyroscope_angular_velocity_tau = mSensor->GyroscopeAngle(Q_Tau);


    Vector3 stabilization_tau_moment_angle = -coff_battervorta_c1 * (accelerometer_angular_orientation_tau) -
                                              coff_battervorta_c2 * (gyroscope_angular_velocity_tau);

    auto I = converAddaptive(mRigidBody_Base->PhysRigidBody()->getLocalInertiaTensor());
    stab_moment = stabilization_tau_moment_angle * I;

    //-----------------------------------------------------------------------//

}


//========================================================================================================//


void IQuadrocopterDynamica::UpdateStabilizationFreeControl(float _time_step)
{
    //    Quaternion orientaton_body = m_PhysicsBody->GetTransform().GetRotation();
    //    scalar pitch = orientaton_body.GetEulerAngles().x;
    //    scalar roll  = orientaton_body.GetEulerAngles().z;


    Vector3 Force = Vector3::Y * mRigidBody_Base->GetTransform().GetBasis() * m_Power;// * cos(pitch)*cos(roll);;
    Vector3 Moment;
    UpdateStabilizationAngle(Moment,m_TauAngles,_time_step);

    scalar inverse_time_step = (1./_time_step);
    mRigidBody_Base->applyWorldForceAtCenterOfMass(Force * inverse_time_step);
    mRigidBody_Base->applyWorldTorque(Moment * inverse_time_step);

    scalar k = 1.4851*10e-4;
    scalar b = 0.05;
    scalar l = m_Lenght;
    scalar F = Force.Length();

    scalar speed_length = 20.f;
    m_W[0] = ISqrt(F/4*k - Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[1] = ISqrt(F/4*k - Moment.x/2*k*l + Moment.y/4*b) * speed_length;
    m_W[2] = ISqrt(F/4*k + Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[3] = ISqrt(F/4*k + Moment.x/2*k*l + Moment.y/4*b) * speed_length;

    //std::cout << m_W[0] << " " << m_W[1] << " " << m_W[2] << " " << m_W[0] << std::endl;
}

void IQuadrocopterDynamica::UpdateStabilizationControlHeight(scalar expected_height, float _time_step)
{
    Vector3 Force;
    Vector3 Moment;
    UpdateStabilizationHeight(Force,expected_height,_time_step);
    UpdateStabilizationAngle(Moment,m_TauAngles,_time_step);

    scalar inverse_time_step = (1./_time_step);
    mRigidBody_Base->applyWorldForceAtCenterOfMass(Force * inverse_time_step);
    mRigidBody_Base->applyWorldTorque(Moment * inverse_time_step);

    scalar k = 1.4851*10e-4;
    scalar b = 0.05;
    scalar l = m_Lenght;
    scalar F = Force.Length();

    scalar speed_length = 20.f;
    m_W[0] = ISqrt(F/4*k - Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[1] = ISqrt(F/4*k - Moment.x/2*k*l + Moment.y/4*b) * speed_length;
    m_W[2] = ISqrt(F/4*k + Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[3] = ISqrt(F/4*k + Moment.x/2*k*l + Moment.y/4*b) * speed_length;
}



void IQuadrocopterDynamica::UpdateStabilizationControlPosition(const Vector3 &expected_coords, scalar _time_step)
{
    scalar relaxation = 0.05;
    scalar desired_ang = (m_AngleYaw - m_TauAngles.y) * relaxation;
    m_TauAngles.y += desired_ang;

    Vector3 Force;
    Vector3 Moment;
    UpdateStabilizationHeight(Force,expected_coords.y,_time_step);
    UpdateStabilizationPosition(m_TauAngles,expected_coords,_time_step);
    UpdateStabilizationAngle(Moment,m_TauAngles,_time_step);

    scalar inverse_time_step = (1./_time_step);
    mRigidBody_Base->applyWorldForceAtCenterOfMass(Force * inverse_time_step);
    mRigidBody_Base->applyWorldTorque(Moment * inverse_time_step*inverse_time_step);

    scalar k = 1.4851*10e-4;
    scalar b = 0.05;
    scalar l = m_Lenght;
    scalar F = Force.Length();

    scalar speed_length = 20.f;
    m_W[0] = ISqrt(F/4*k - Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[1] = ISqrt(F/4*k - Moment.x/2*k*l + Moment.y/4*b) * speed_length;
    m_W[2] = ISqrt(F/4*k + Moment.z/2*k*l - Moment.y/4*b) * speed_length;
    m_W[3] = ISqrt(F/4*k + Moment.x/2*k*l + Moment.y/4*b) * speed_length;

    //    auto Q = m_PhysicsBody->GetTransform().GetRotation();
    //    auto P = m_PhysicsBody->GetTransform().GetPosition();

    //    m_PhysicsBody->ApplyImpulse( Q * Vector3::Y * m_W[0] , P + Q * Vector3::X * m_Lenght);
    //    m_PhysicsBody->ApplyImpulse( Q * Vector3::Y * m_W[1] , P + Q * Vector3::Z * m_Lenght);
    //    m_PhysicsBody->ApplyImpulse( Q * Vector3::Y * m_W[2] , P - Q * Vector3::X * m_Lenght);
    //    m_PhysicsBody->ApplyImpulse( Q * Vector3::Y * m_W[3] , P - Q * Vector3::Z * m_Lenght);

    //    std::cout << m_W[0] << " " << m_W[1] << " " << m_W[2] << " " << m_W[3] << std::endl;
}

//========================================================================================================//

IComponentRigidBody *IQuadrocopterDynamica::PhysicsBody() const
{
    return mRigidBody_Base;
}

void IQuadrocopterDynamica::SetTauAngles(const Vector3 &TauAngles)
{
    m_TauAngles = TauAngles;
}

Vector3 IQuadrocopterDynamica::Forward() const
{
    return m_Forward;
}

Vector3 IQuadrocopterDynamica::Left() const
{
    return m_Left;
}













