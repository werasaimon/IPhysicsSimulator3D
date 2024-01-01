#include "IComponentCamera.h"


IComponentCamera::IComponentCamera()
  : m_Camera(new IQCamera)
{
    m_Eye = Vector3::Z * -10.f;
    m_Center = Vector3::ZERO;
    m_Up = Vector3::Y;
}


IComponentCamera::IComponentCamera(IQCamera *_Camera)
  : m_Camera(std::move(_Camera))
{
    m_Eye = Vector3::Z * -10.f;
    m_Center = Vector3::ZERO;
    m_Up = Vector3::Y;
}

IComponentCamera::~IComponentCamera()
{
    if(m_Camera)
    {
        delete m_Camera;
        m_Camera = nullptr;
    }
}

void IComponentCamera::InitPerspective(scalar FieldOfView, scalar aspect, scalar NearPlane, scalar FarPlane)
{
    m_Camera->SetNear(NearPlane);
    m_Camera->SetFar(FarPlane);
    m_Camera->SetAspect(aspect);
    m_Camera->SetAngle(FieldOfView);
}

void IComponentCamera::Update()
{
    m_Camera->SetTransformMatrix(mTransformMatrix);
}

void IComponentCamera::LookAt()
{
    m_Camera->LookAt( m_Eye , m_Center , m_Up );
}

Vector3 IComponentCamera::Eye() const
{
    return m_Eye;
}

Vector3 IComponentCamera::Center() const
{
    return m_Center;
}

Vector3 IComponentCamera::Up() const
{
    return m_Up;
}

void IComponentCamera::setEye(const Vector3 &newEye)
{
    m_Eye = newEye;
}

void IComponentCamera::setCenter(const Vector3 &newCenter)
{
    m_Center = newCenter;
}

void IComponentCamera::setUp(const Vector3 &newUp)
{
    m_Up = newUp;
}

IQCamera *IComponentCamera::Camera() const
{
    return m_Camera;
}
