#ifndef ICOMPONENTCAMERA_H
#define ICOMPONENTCAMERA_H

#include "IGeometry/IQCamera.h"
#include <IEngineComponent/IComponents.hpp>
#include <IEngine/engine.hpp>

using namespace IEngine;
using namespace IMath;

class IComponentCamera : public IComponentObject2
{
private:
    // Запрещаем копирование и присваивание экземпляра класса.
    IComponentCamera(const IComponentCamera&) = delete;
    IComponentCamera& operator=(const IComponentCamera&) = delete;

public:

     IComponentCamera();
     IComponentCamera(IQCamera *_Camera);
    ~IComponentCamera();

    void InitPerspective(scalar FieldOfView, scalar aspect, scalar NearPlane, scalar FarPlane);
    void Update();
    void LookAt();


//    void DollyZoomFOV( float fov )
//    {
//        m_Camera->DollyZoom(fov);
//    }


//    void InitTransform()
//    {
//        m_Camera->LookAt( m_Eye , m_Center , m_Up );
//        SetTransformMatrix(m_Camera->ViewMatrix().GetInverse());
//    }


//    void TargetVision(const Vector3& target , const Vector3& _up = Vector3::Y)
//    {
//        mTransformMatrix.SetRotation( Quaternion::LookAtRH( mTransformMatrix.GetTranslation(), target, _up)
//                                     .GetConjugate().GetRotMatrix() );
//    }

    Vector3 Eye() const;
    Vector3 Center() const;
    Vector3 Up() const;

    void setEye(const Vector3 &newEye);
    void setCenter(const Vector3 &newCenter);
    void setUp(const Vector3 &newUp);

    IQCamera *Camera() const;

private:

    IQCamera *m_Camera;

    Vector3 m_Eye;
    Vector3 m_Center;
    Vector3 m_Up;


};

#endif // ICOMPONENTCAMERA_H
