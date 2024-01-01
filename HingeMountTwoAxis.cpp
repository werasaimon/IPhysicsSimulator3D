#include "HingeMountTwoAxis.h"
#include <glwidget.h>

#include <GL/gl.h>
#include <GL/glu.h>


HingeMountTwoAxis::HingeMountTwoAxis(GLWidget *_globalScene_,
                                     IComponentRigidBody * body1,
                                     IComponentRigidBody * body2,
                                     const Vector3 &_origin,
                                     const Vector3 &_axis1,
                                     const Vector3 &_axis2)
    : m_AnchorWorldPosition1(_origin),
      m_AnchorWorldPosition2(_origin),
      m_Axis1(_axis1),
      m_Axis2(_axis2)
{

    Vector3 extendet(1);
    Transform transform(m_AnchorWorldPosition1);
    m_RigidBodyOuterPortion = new IComponentRigidBody(transform,_globalScene_->CPhysicsWorld());
    auto geometry_mesh_box_1 = new IComponentMesh(MeshGenerator::EllipsoidDescriptor(extendet));
    auto collision_shape_box_1 = _globalScene_->CPhysInstrument()->CCreateSpereShape(extendet.Length() * 0.5);
    geometry_mesh_box_1->SetTransform(transform);
    m_RigidBodyOuterPortion->AddCollider2(collision_shape_box_1 , geometry_mesh_box_1);
    _globalScene_->CScene()->AddComponent(geometry_mesh_box_1);

    m_RigidBodyOuterPortion->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    //-------------------------------------------------------------------------//

    rp3d::HingeJointInfo info_hinge_1(m_RigidBodyOuterPortion->PhysRigidBody(),
                                      body1->PhysRigidBody(),
                                      converAddaptive(m_AnchorWorldPosition1),
                                      converAddaptive(m_Axis1));

    m_HingeConstraintJoint1 = _globalScene_->createJoint(info_hinge_1);

    //-------------------------------------------------------------------------//

    rp3d::HingeJointInfo info_hinge_2(m_RigidBodyOuterPortion->PhysRigidBody(),
                                      body2->PhysRigidBody(),
                                      converAddaptive(m_AnchorWorldPosition2),
                                      converAddaptive(m_Axis2));

    m_HingeConstraintJoint2 = _globalScene_->createJoint(info_hinge_2);

    //-------------------------------------------------------------------------//

    _globalScene_->CPhysicsWorld()->addNoCollisionPair(m_RigidBodyOuterPortion,body1);
    _globalScene_->CPhysicsWorld()->addNoCollisionPair(m_RigidBodyOuterPortion,body2);

    //-------------------------------------------------------------------------//
}


HingeMountTwoAxis::HingeMountTwoAxis(GLWidget *_globalScene_ ,
                                     IComponentRigidBody *body1,
                                     IComponentRigidBody *body2,
                                     const Vector3& _origin1 ,
                                     const Vector3& _origin2 ,
                                     const Vector3& _axis1,
                                     const Vector3& _axis2)
    : m_AnchorWorldPosition1(_origin1),
      m_AnchorWorldPosition2(_origin2),
      m_Axis1(_axis1),
      m_Axis2(_axis2)
{

    Vector3 extendet(1);
    Transform transform(m_AnchorWorldPosition1);
    m_RigidBodyOuterPortion = new IComponentRigidBody(transform,_globalScene_->CPhysicsWorld());
    auto geometry_mesh_box_1 = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet));
    auto collision_shape_box_1 = _globalScene_->CPhysInstrument()->CCreateBoxShape(extendet);
    geometry_mesh_box_1->SetTransform(transform);
    m_RigidBodyOuterPortion->AddCollider2(collision_shape_box_1 , geometry_mesh_box_1);
  //  _globalScene_->CScene()->AddComponent(geometry_mesh_box_1);

    m_RigidBodyOuterPortion->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    //-------------------------------------------------------------------------//

    rp3d::HingeJointInfo info_hinge_1(m_RigidBodyOuterPortion->PhysRigidBody(),
                                      body1->PhysRigidBody(),
                                      converAddaptive(m_AnchorWorldPosition1),
                                      converAddaptive(m_Axis1));

    m_HingeConstraintJoint1 = _globalScene_->createJoint(info_hinge_1);

    //-------------------------------------------------------------------------//

    rp3d::HingeJointInfo info_hinge_2(m_RigidBodyOuterPortion->PhysRigidBody(),
                                      body2->PhysRigidBody(),
                                      converAddaptive(m_AnchorWorldPosition2),
                                      converAddaptive(m_Axis2));

    m_HingeConstraintJoint2 = _globalScene_->createJoint(info_hinge_2);

    //-------------------------------------------------------------------------//

    _globalScene_->CPhysicsWorld()->addNoCollisionPair(m_RigidBodyOuterPortion,body1);
    _globalScene_->CPhysicsWorld()->addNoCollisionPair(m_RigidBodyOuterPortion,body2);

    //-------------------------------------------------------------------------//
}

void HingeMountTwoAxis::Draw()
{

    draw_line( m_RigidBodyOuterPortion->GetTransform().GetPosition(),
               m_RigidBodyOuterPortion->GetTransform() * ( m_Axis1 * 5.f) , Vector3(1,0,0) );


    draw_line( m_RigidBodyOuterPortion->GetTransform().GetPosition(),
               m_RigidBodyOuterPortion->GetTransform() * ( m_Axis2 * 5.f) , Vector3(0,1,0));

}

IComponentRigidBody *HingeMountTwoAxis::RigidBodyOuterPortion() const
{
    return m_RigidBodyOuterPortion;
}


IComponentConstraitJoint *HingeMountTwoAxis::GetHingeConstraintJoint1() const
{
    return m_HingeConstraintJoint1;
}

IComponentConstraitJoint *HingeMountTwoAxis::GetHingeConstraintJoint2() const
{
    return m_HingeConstraintJoint2;
}

Vector3 HingeMountTwoAxis::GetAnchorWorldPosition1() const
{
    return m_AnchorWorldPosition1;
}

Vector3 HingeMountTwoAxis::GetAnchorWorldPosition2() const
{
    return m_AnchorWorldPosition2;
}

Vector3 HingeMountTwoAxis::GetAxis1() const
{
    return m_Axis1;
}

Vector3 HingeMountTwoAxis::GetAxis2() const
{
    return m_Axis2;
}




