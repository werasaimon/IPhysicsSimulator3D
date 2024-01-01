#include "ActuatorDynamic.h"
#include <IEngine/reactphysics3d/reactphysics3d.h>
#include <glwidget.h>



//#include <GL/freeglut.h>
//#include <QDebug>

ActuatorDynamic::ActuatorDynamic(const Vector3 &point1, const Vector3 &point2 ,  GLWidget *_globalScene_, float angle)
  : m_Point1(point1),
    m_Point2(point2),
    m_RigidBodyShtok1(nullptr),
    m_RigidBodyShtok2(nullptr)
{


    m_CofficientPos = 4.0;
    m_CofficientVel = 0.99;

    m_MaxVelocity =  10;
    m_MinVelocity = -10;

    /**/

    m_Direction = Vector3::Y;

    scalar seet_off = 0.2f;

    scalar high  = (point1 - point2).Length();
    m_Length = high;

    assert(high > 0);
    Vector3 center = point1 - (point1 - point2) * 0.5f;

    m_Center1 = center;


    //scalar L = (m_Center1 - point2).Length();


    Quaternion Q = Quaternion::FromAngleAxis(Vector3::Z, IMath::IDegreesToRadians(90.f));
    Quaternion Q1 = Quaternion::FromAngleAxis(Vector3::Y, IMath::IDegreesToRadians(angle));
    Quaternion Orientation = Quaternion::SlerpToVector(Vector3::X,(point1 - point2).GetUnit()) * Q * Q1;
    Orientation.Normalize();

    m_OrientDirection = Quaternion::SlerpToVector(Vector3::Z,(point1 - point2).GetUnit()) * Q1;

//    IPlane planeY(Vector3::Y,point1);
//    IPlane planeX(Vector3::X,point1);
//    Quaternion Or0 = Quaternion::SlerpToVector(Vector3::X,planeY.ClosestPoint(point1 - point2).GetUnit());
//    Quaternion Or1 = Quaternion::SlerpToVector(Vector3::Y,planeX.ClosestPoint(point1 - point2).GetUnit());
//    Orientation = Or0 * Or1;
//    Orientation.Normalize();

//    AffineTransform affine_transform;
//    affine_transform.RotateAroundLocalPoint(Vector3::X , IMath::IDegreesToRadians(20.f), center );

    Transform trans1(center);
    Transform trans2(center + Vector3::Y * high * seet_off);
    m_RigidBodyShtok1 = new IComponentRigidBody(trans1,_globalScene_->CPhysicsWorld());
    m_RigidBodyShtok2 = new IComponentRigidBody(trans2,_globalScene_->CPhysicsWorld());

//    m_RigidBodyShtok1->SetTransform(trans1);
//    m_RigidBodyShtok2->SetTransform(trans2);

    //scalar high = (point1 - point2).Length();
    Vector3 extendet(1,high,1);
    //Transform init = Transform::Identity();

    auto geometry_mesh_box_1 = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet));
    auto collision_shape_box_1 = _globalScene_->CPhysInstrument()->CCreateBoxShape(extendet);
    geometry_mesh_box_1->SetTransform(trans1);
    m_RigidBodyShtok1->AddCollider2(collision_shape_box_1 , geometry_mesh_box_1);

    //MeshGenerator::CylinderDescriptor descp_cilinder(Vector2(extendet.x,extendet.z) * 0.5,extendet.y);

    auto geometry_mesh_box_2 = new  IComponentMesh(MeshGenerator::CuboidDescriptor(extendet));//IComponentMesh(descp_cilinder);
    auto collision_shape_box_2 = _globalScene_->CPhysInstrument()->CCreateBoxShape(extendet * Vector3(0.5f,1.f,0.5f));
    geometry_mesh_box_2->SetTransform(trans2);
    m_RigidBodyShtok2->AddCollider2(collision_shape_box_2 , geometry_mesh_box_2);

    _globalScene_->CScene()->AddComponent(geometry_mesh_box_1);
    _globalScene_->CScene()->AddComponent(geometry_mesh_box_2);

    m_RigidBodyShtok1->InitTypePhysics(rp3d::BodyType::DYNAMIC);
    m_RigidBodyShtok2->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    rp3d::SliderJointInfo slider_info(m_RigidBodyShtok1->PhysRigidBody(),
                                      m_RigidBodyShtok2->PhysRigidBody(),
                                      converAddaptive(center),
                                      converAddaptive(Vector3::Y),
                                      -m_Length * 0.5,
                                       m_Length * ((1.f - seet_off)));

    slider_info.isLimitEnabled = true;
    slider_info.isMotorEnabled = true;
    slider_info.isCollisionEnabled = true;
    slider_info.isUsingLocalSpaceAnchors = false;

    m_SliderConstraintJoint = new IComponentConstraitJoint(slider_info,_globalScene_->CPhysicsWorld());

    _globalScene_->CPhysicsWorld()->addNoCollisionPair(m_RigidBodyShtok1,
                                                       m_RigidBodyShtok2);


    SetTransform(Transform(center,Orientation));




            //    Transform t = Transform(affine_transform.GetTransformMatrix());
            //    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->setTransform(converAddaptive(t));
            //    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody2()->setTransform(converAddaptive(t));


            //    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->setTransform(converAddaptive(Transform(trans1.GetPosition(),Orientation)));
            //    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody2()->setTransform(converAddaptive(Transform(trans2.GetPosition(),Orientation)));


    m_RigidBodyShtok2->PhysRigidBody()->setTransform( m_RigidBodyShtok1->PhysRigidBody()->getTransform() *
                                                      converAddaptive(Transform(Vector3::Y * 3.f)));
}





void ActuatorDynamic::Initilization()
{

}

void ActuatorDynamic::setVelocity(const scalar &_velocity_pwm)
{
    m_Velocity =  _velocity_pwm * m_CofficientVel;
    rp3d::SliderJoint* joint = m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>();
    joint->enableMotor(true);
    joint->setMaxMotorForce(10000);
    float eps = 0.1f;
    if( (joint->getTranslation() > joint->getMaxTranslationLimit() - eps && m_Velocity >= 0) ||
        (joint->getTranslation() < joint->getMinTranslationLimit() + eps && m_Velocity <= 0) )
    {
        joint->setMotorSpeed(0);
    }
    else
    {
        joint->setMotorSpeed(m_Velocity);
    }
}

void ActuatorDynamic::SetPWM(float _pwm_vel)
{
    this->setVelocity(_pwm_vel);
}

//void ActuatorDynamic::UpdatePID(const scalar &_pos)
//{
//    // m_CofficientPos = 50.f;
//    m_Position = getReadEncoder();
//    float fine_pos = _pos;
//    float error = ((m_Position - fine_pos) * m_CofficientPos);

//    error = IClamp(error, float(m_MinVelocity), float(m_MaxVelocity));
//    setVelocity(-error);
//    //m_Integral += error * 0.005f;
//}

void ActuatorDynamic::SetTransform(const Transform &_transform)
{

//    auto trans1 = m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->getTransform();
//    auto trans2 = m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody2()->getTransform();

    //        Vector3 diri = converAddaptive(trans1.getPosition() - trans2.getPosition());
    //        Vector3 posi = converAddaptive(trans1.getPosition());
//    Transform tran2( _transform.GetPosition() + _transform.GetRotation() * Vector3::Y * 2.f , _transform.GetRotation() );

    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody2()->setTransform(converAddaptive(_transform));
    m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->setTransform(converAddaptive(_transform));
}

void ActuatorDynamic::Draw()
{
    //rp3d::SliderJoint* joint = m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>();
    //qDebug() << joint->getTranslation();

//    glPushMatrix();
//    Vector3 pos = converAddaptive(m_RigidBodyShtok1->PhysRigidBody()->getTransform().getPosition() +
//                                  m_RigidBodyShtok1->PhysRigidBody()->getLocalCenterOfMass());
//    glTranslatef(pos.x,pos.y,pos.z);
//    glutSolidSphere(0.5,10,10);
//    glPopMatrix();


    Vector3 a = converAddaptive( m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->getTransform().getPosition());
    Vector3 b = converAddaptive( m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getBody1()->getTransform().getPosition());
    b += getWorldDirection() * getTranslation();

    draw_line(a,b,Vector3(0,0,1));


    Vector3 min = converAddaptive( m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getMinTranslationLimit() * converAddaptive(m_Direction));
    Vector3 max = converAddaptive( m_SliderConstraintJoint->GetTypeJoint<rp3d::SliderJoint>()->getMaxTranslationLimit() * converAddaptive(m_Direction));
    min =  m_RigidBodyShtok1->GetTransform() * min;
    max =  m_RigidBodyShtok1->GetTransform() * max;

    draw_line(min,max,Vector3(0,1,1));

        //    glPushMatrix();
        //    Vector3 pos2 = converAddaptive(m_RigidBodyShtok2->PhysRigidBody()->getTransform().getPosition() +
        //                                   m_RigidBodyShtok2->PhysRigidBody()->getLocalCenterOfMass());
        //    glTranslatef(pos2.x,pos2.y,pos2.z);
        //    glutSolidSphere(0.5,10,10);
        //    glPopMatrix();

        //    glPushMatrix();
        //    glColor3f(0,1,0);
        //    glBegin(GL_LINES);
        //    glVertex3fv(m_Point1);
        //    glVertex3fv(m_Point2);
        //    glEnd();
        //    glPopMatrix();




//    glPushMatrix();
//    glColor3f(0,1,1);
//    glBegin(GL_LINES);
//    glVertex3fv(m_Center1);
//    rp3d::Vector3 v = converAddaptive(m_Center1) + converAddaptive(QuatRot) * rp3d::Vector3(0,10,0);
//    glVertex3f(v.x,v.y,v.z);
//    glEnd();
//    glPopMatrix();


    /**
    glPushMatrix();
    glTranslatef(m_Center1.x, m_Center1.y, m_Center1.z);
    glutSolidSphere(0.5,10,10);
    glPopMatrix();
    **/


    //        glPushMatrix();
    //        glTranslatef(m_Center2.x, m_Center2.y, m_Center2.z);
    //        glutSolidSphere(0.5,10,10);
    //        glPopMatrix();
}

IComponentConstraitJoint *ActuatorDynamic::SliderConstraintJoint() const
{
    return m_SliderConstraintJoint;
}

IComponentRigidBody *ActuatorDynamic::RigidBody1()
{
    return m_RigidBodyShtok1;
}

IComponentRigidBody *ActuatorDynamic::RigidBody2()
{
    return m_RigidBodyShtok2;
}



IComponentRigidBody *ActuatorDynamic::BaseBody()
{
    return m_RigidBodyShtok1;
}

IComponentRigidBody *ActuatorDynamic::ShtokBody()
{
    return m_RigidBodyShtok2;
}

Quaternion ActuatorDynamic::GetOrientDirection() const
{
    return m_OrientDirection;
}









