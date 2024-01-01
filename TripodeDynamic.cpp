#include "TripodeDynamic.h"
#include "glwidget.h"

TripodeDynamic::TripodeDynamic(GLWidget *_globalScene_)
    : TripodeHardware(_globalScene_)
{

    Vector3 actuator1_tanget_left;
    Vector3 actuator1_tanget_up;
    Vector3::BiUnitOrthogonalVector(m_Actuator1->getWorldDirection(),actuator1_tanget_up,actuator1_tanget_left);


    Vector3 actuator2_tanget_left;
    Vector3 actuator2_tanget_up;
    Vector3::BiUnitOrthogonalVector(m_Actuator2->getWorldDirection(),actuator2_tanget_up,actuator2_tanget_left);

    //=====================================================//

//    IPlane plane( Vector3::Y , Vector3::ZERO);
//    Quaternion quad1 = Quaternion::SlerpToVector(Vector3::Z , plane.ClosestPoint(a_p2-a_p1)).GetInverse();
//    Quaternion quad2 = Quaternion::SlerpToVector(Vector3::Z , plane.ClosestPoint(b_p2-b_p1)).GetInverse();

//    Vector3 point_hinge_attachment_1 = m_Actuator1->getColosetstPoint();//  a_p2 + m_Actuator1->getWorldDirection() * m_Actuator1->Length() * 0.0f;
//    Vector3 point_hinge_attachment_2 = m_Actuator2->getColosetstPoint();// b_p2 + m_Actuator2->getWorldDirection() * m_Actuator2->Length() * 0.4f;

    //=====================================================//

    Vector3 extendet_helf(2,1,14);
    Vector3 point_base = Vector3::Z * (20) + m_Origin + Vector3::Y * 3;
    Transform trans_base(point_base);
    auto RigidBody_Base = new IComponentRigidBody(trans_base,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_base = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_helf));
    auto collision_shape_box_base = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_helf);
    //geometry_mesh_box_base->SetTransform(trans_base);

    Transform transform = Transform::Identity();
    RigidBody_Base->AddCollider2(collision_shape_box_base , geometry_mesh_box_base ,&transform);
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_base);
    RigidBody_Base->InitTypePhysics(rp3d::BodyType::DYNAMIC);


/**/
    //=====================================================//


    Vector3 extendet_fixed(1,1,1);
    Vector3 point_fixed = Vector3::Z * 25 + Vector3::Y * 1 + m_Origin;
    Transform trans_fixed(point_fixed);
    RigidBody_Fixed = new IComponentRigidBody(trans_fixed,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_fixed = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_fixed));
    auto collision_shape_box_fixed = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_fixed);
    geometry_mesh_box_fixed->SetTransform(trans_fixed);
    RigidBody_Fixed->AddCollider2(collision_shape_box_fixed , geometry_mesh_box_fixed);
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_fixed);
    RigidBody_Fixed->InitTypePhysics(rp3d::BodyType::DYNAMIC);


    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(RigidBody_Fixed,RigidBody_Base);


/**/

    //=====================================================//

    m_Hinge0 = new HingeMountTwoAxis(mGlobalScene,
                                     RigidBody_Fixed, RigidBody_Base,
                                     point_fixed,
                                     Vector3::X,
                                     Vector3::Y);


    //=====================================================//

    m_Hinge1 = new HingeMountTwoAxis(mGlobalScene,
                                     m_Actuator1->ShtokBody(),
                                     RigidBody_Base,
                                     m_Actuator1->getColosetstPoint(),
                                     Vector3::Y,
                                     Vector3::X);


    //=====================================================//

    m_Hinge2 = new HingeMountTwoAxis(mGlobalScene,
                                     m_Actuator2->ShtokBody(),
                                     RigidBody_Base,
                                     m_Actuator2->getColosetstPoint(),
                                     Vector3::Y,
                                     -Vector3::X);

    //==============================================================================================//

    /**/

    Vector3 extendet_fixola_1(0.5,0.5,0.5);
    Vector3 point_fixola_1 = m_Actuator1->getBottomPoint() - Vector3::Y * 1.5;
    Transform trans_fixola_1(point_fixola_1);
    RigidBody_Fixola_1 = new IComponentRigidBody(trans_fixola_1,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_fixola_1 = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_fixola_1));
    auto collision_shape_box_fixola_1 = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_fixola_1);
    geometry_mesh_box_fixola_1->SetTransform(trans_fixola_1);
    RigidBody_Fixola_1->AddCollider2( collision_shape_box_fixola_1 , geometry_mesh_box_fixola_1);
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_fixola_1);

    RigidBody_Fixola_1->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    //-----------------------------------------------------------------------------------------------//

    Vector3 extendet_fixola_2(0.5,0.5,0.5);
    Vector3 point_fixola_2 = m_Actuator2->getBottomPoint() - Vector3::Y * 1.5;
    Transform trans_fixola_2(point_fixola_2);
    RigidBody_Fixola_2 = new IComponentRigidBody(trans_fixola_2,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_fixola_2 = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_fixola_2));
    auto collision_shape_box_fixola_2 = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_fixola_2);
    geometry_mesh_box_fixola_2->SetTransform(trans_fixola_2);
    RigidBody_Fixola_2->AddCollider2( collision_shape_box_fixola_2 , geometry_mesh_box_fixola_2);
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_fixola_2);

    RigidBody_Fixola_2->InitTypePhysics(rp3d::BodyType::DYNAMIC);


    //------------------------------------------------------------------------------------------------//

    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(m_Actuator1->ShtokBody(),RigidBody_Fixola_1);
    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(m_Actuator1->BaseBody(),RigidBody_Fixola_1);
    //mGlobalScene->CPhysicsWorld()->addNoCollisionPair(RigidBody_Bottom_1,RigidBody_Fixola_1);

    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(m_Actuator2->ShtokBody(),RigidBody_Fixola_2);
    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(m_Actuator2->BaseBody(),RigidBody_Fixola_2);
    //mGlobalScene->CPhysicsWorld()->addNoCollisionPair(RigidBody_Bottom_2,RigidBody_Fixola_2);

    //-------------------------------------------------------------------------------------------------//

    pos_A = point_fixed;
    pos_B = point_fixola_1;
    pos_C = point_fixola_2;


    m_Hinge3 = new HingeMountTwoAxis(mGlobalScene,
                                     m_Actuator1->BaseBody(),
                                     RigidBody_Fixola_1,
                                     m_Actuator1->getBottomPoint(),
                                     Cross(Vector3::Y,m_Actuator1->getWorldDirection()),
                                     Vector3::Y);

    m_Hinge4 = new HingeMountTwoAxis(mGlobalScene,
                                     m_Actuator2->BaseBody(),
                                     RigidBody_Fixola_2,
                                     m_Actuator2->getBottomPoint(),
                                     -Cross(Vector3::Y,m_Actuator2->getWorldDirection()),
                                     Vector3::Y);



    //-------------------------------------------------------------------------------------------------//


    Vector3 extendet_visible(4,2,4);
    Vector3 point_visible = Vector3::Z * 30 + Vector3::Y * 2.f + m_Origin;
    Transform trans_visible(point_visible);
    RigidBody_VisionModul = new IComponentRigidBody(point_visible,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_visible = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_visible));
    auto collision_shape_box_visible = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_visible);
    geometry_mesh_box_visible->SetTransform(trans_visible);
    RigidBody_VisionModul->AddCollider2( collision_shape_box_visible , geometry_mesh_box_visible );
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_visible);
    RigidBody_VisionModul->InitTypePhysics(rp3d::BodyType::DYNAMIC);



    //RigidBody_VisionModul->PhysRigidBody()->setMass(4);

    rp3d::FixedJointInfo fixed_joint_info(RigidBody_Base->PhysRigidBody(),
                                          RigidBody_VisionModul->PhysRigidBody(),
                                          converAddaptive(point_visible));
    auto joint_fixed = mGlobalScene->createJoint(fixed_joint_info);

    //-------------------------------------------------------------------------------------------------//


    Vector3 extendet_forward(2,2,2);
    point_forward = point_visible + Vector3::Y * point_fixola_1.y + Vector3::Z * 2;
    Transform trans_forward(point_forward);
    RigidBody_Forward = new IComponentRigidBody(point_forward,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_forward = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_forward));
    auto collision_shape_box_forward = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_forward);
    geometry_mesh_box_forward->SetTransform(trans_forward);
    RigidBody_Forward->AddCollider2( collision_shape_box_forward , geometry_mesh_box_forward );
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_forward);
    RigidBody_Forward->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    rp3d::FixedJointInfo fixed2_joint_info(RigidBody_Fixed->PhysRigidBody(),
                                           RigidBody_Forward->PhysRigidBody(),
                                           converAddaptive(point_forward));
    auto joint_fixed2 = mGlobalScene->createJoint(fixed2_joint_info);


    /**/


    rp3d::FixedJointInfo fixed3_joint_info(RigidBody_Fixola_1->PhysRigidBody(),
                                           RigidBody_Fixed->PhysRigidBody(),
                                           converAddaptive(point_fixola_1));
    auto joint_fixed3 = mGlobalScene->createJoint(fixed3_joint_info);


    rp3d::FixedJointInfo fixed4_joint_info(RigidBody_Fixola_2->PhysRigidBody(),
                                           RigidBody_Fixed->PhysRigidBody(),
                                           converAddaptive(point_fixola_2));
    auto joint_fixed4 = mGlobalScene->createJoint(fixed4_joint_info);

    //--------------------------------------------------------------------------------------//

    Vector3 cnentroid = (point_forward+point_fixola_1+point_fixola_2)*0.5f;

    rp3d::FixedJointInfo fixed5_joint_info(RigidBody_Fixola_1->PhysRigidBody(),
                                           RigidBody_Forward->PhysRigidBody(),
                                           converAddaptive(point_forward));
    auto joint_fixed5 = mGlobalScene->createJoint(fixed5_joint_info);


    rp3d::FixedJointInfo fixed6_joint_info(RigidBody_Fixola_2->PhysRigidBody(),
                                           RigidBody_Forward->PhysRigidBody(),
                                           converAddaptive(point_forward));
    auto joint_fixed6 = mGlobalScene->createJoint(fixed6_joint_info);

    rp3d::FixedJointInfo fixed7_joint_info(RigidBody_Fixola_2->PhysRigidBody(),
                                           RigidBody_Fixola_1->PhysRigidBody(),
                                           converAddaptive((point_fixola_1+point_fixola_2)*0.5f));
    auto joint_fixed7 = mGlobalScene->createJoint(fixed7_joint_info);

    //--------------------------------------------------------------------------------------//

    //m_InitBasis = Quaternion::IDENTITY;
    m_OrientationSensor = new IOrientationSensor(RigidBody_VisionModul);

    //--------------------------------------------------------------------------------------//


    Vector3 extendet_gun(2,2,25);
    Vector3 point_gun = Vector3::Y * 5 + Vector3::Z * 15;
    Transform trans_gun(point_gun);
    RigidBody_Gun = new IComponentRigidBody(point_gun,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_gun = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_gun));
    auto collision_shape_box_gun = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_gun);
    geometry_mesh_box_gun->SetTransform(trans_gun);
    RigidBody_Gun->AddCollider2( collision_shape_box_gun , geometry_mesh_box_gun );
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_gun);
    RigidBody_Gun->InitTypePhysics(rp3d::BodyType::DYNAMIC);


    rp3d::FixedJointInfo fixed8_joint_info(RigidBody_Base->PhysRigidBody(),
                                           RigidBody_Gun->PhysRigidBody(),
                                           converAddaptive(point_gun));
    auto joint_fixed8 = mGlobalScene->createJoint(fixed8_joint_info);



    rp3d::FixedJointInfo fixed9_joint_info(RigidBody_Base->PhysRigidBody(),
                                           RigidBody_Gun->PhysRigidBody(),
                                           converAddaptive(point_gun - Vector3::Z * 10));
    auto joint_fixed9 = mGlobalScene->createJoint(fixed9_joint_info);

    //--------------------------------------------------------------------------------------//

    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(RigidBody_Gun,m_Hinge1->RigidBodyOuterPortion());
    mGlobalScene->CPhysicsWorld()->addNoCollisionPair(RigidBody_Gun,m_Hinge2->RigidBodyOuterPortion());

}


IOrientationSensor *TripodeDynamic::GetOrientationSensor() const
{
    return m_OrientationSensor;
}

void TripodeDynamic::Shot()
{
    Vector3 direction = RigidBody_Gun->GetTransform().GetRotation() * Vector3::Z;
    Vector3 point = converAddaptive(RigidBody_Gun->PhysRigidBody()->getTransform().getPosition());

    Vector3 extendet_bullet(1,1,1);
    Vector3 point_bullet = point + direction  * 15;
    Transform trans_bullet(point_bullet);
    auto RigidBody_bullet = new IComponentRigidBody(point_bullet,mGlobalScene->CPhysicsWorld());
    auto geometry_mesh_box_bullet = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_bullet));
    auto collision_shape_box_bullet = mGlobalScene->CPhysInstrument()->CCreateBoxShape(extendet_bullet);
    geometry_mesh_box_bullet->SetTransform(trans_bullet);
    RigidBody_bullet->AddCollider2( collision_shape_box_bullet , geometry_mesh_box_bullet );
    mGlobalScene->CScene()->AddComponent(geometry_mesh_box_bullet);
    RigidBody_bullet->InitTypePhysics(rp3d::BodyType::DYNAMIC);

    RigidBody_bullet->PhysRigidBody()->applyLocalForceAtCenterOfMass(converAddaptive(direction * 10000.f));
    RigidBody_Gun->PhysRigidBody()->applyLocalForceAtCenterOfMass(converAddaptive(direction * -250.f));

}


void TripodeDynamic::Draw()
{
     m_Actuator1->Draw();
     m_Actuator2->Draw();

     m_Hinge0->Draw();
     m_Hinge1->Draw();
     m_Hinge2->Draw();
     m_Hinge3->Draw();
     m_Hinge4->Draw();


     Vector3 A = RigidBody_Fixola_1->GetTransform().GetPosition();
     Vector3 B = RigidBody_Fixola_2->GetTransform().GetPosition();
     Vector3 C = RigidBody_Fixed->GetTransform().GetPosition();
     Vector3 D = RigidBody_Forward->GetTransform().GetPosition();

     draw_line(B,A);
     draw_line(C,A);
     draw_line(B,C);
     draw_line(C,D);


     Vector3 direction = RigidBody_Gun->GetTransform().GetRotation() * Vector3::Z;
     Vector3 point = RigidBody_Gun->GetTransform().GetPosition();

     draw_line(point,point+direction * 1000000);
}




