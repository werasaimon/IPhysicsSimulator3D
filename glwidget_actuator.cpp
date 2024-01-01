#include "glwidget_actuator.h"



GLWidget_Actuator::GLWidget_Actuator(QWidget *parent)
    : GLWidget(parent)
{

}

GLWidget_Actuator::~GLWidget_Actuator()
{

}


void GLWidget_Actuator::initializeGL()
{
    GLWidget::initializeGL();

    //-------------------------------------------//

    m_CScene->Descriptor().m_IsDrawLines = true;
    m_CScene->Descriptor().m_IsDrawFill = false;
    m_CScene->Descriptor().m_IsDynamics = false;

    //-------------------------------------------//

    Vector3 pos = Vector3::Y * 0;
    Vector3 p1 = (Vector3::Z) * 5 + Vector3::Y * 2;
    Vector3 p2 = (Vector3::Z) * -5;
    m_Actuator = new ActuatorDynamic(p1+pos,p2+pos,this);

    //---------------------------------------------------//

    Vector3 extendet(50,5,50);
    Transform base_trans(Vector3(0,-5,0));
    auto m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    auto  collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    MeshGenerator::CuboidDescriptor desc_base(extendet);
    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    base_mesh->setCollider(collider_base);
    m_CScene->AddComponent( base_mesh );

    //---------------------------------------------------//

//    CPhysicsWorld()->addNoCollisionPair(m_CRigidBody_Base,m_Actuator->RigidBody1());
//    CPhysicsWorld()->addNoCollisionPair(m_CRigidBody_Base,m_Actuator->RigidBody2());

}



void GLWidget_Actuator::update_scene()
{
    GLWidget::update_scene();

    //------------------------------------//

    if(m_CScene->Descriptor().m_IsDynamics == true)
    {
       m_Actuator->UpdatePID(pos);
    }

    //------------------------------------//

    if(mKeys[Qt::Key_P] == true)
    {
       m_CScene->Descriptor().m_IsDynamics = true;
    }
}

void GLWidget_Actuator::paintGL()
{
    GLWidget::paintGL();

    //------------------------//

    m_Actuator->Draw();

    //------------------------//
}
