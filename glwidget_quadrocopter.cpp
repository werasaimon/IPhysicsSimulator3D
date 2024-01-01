#include "glwidget_quadrocopter.h"

GLWidget_Quadrocopter::GLWidget_Quadrocopter(QWidget *parent)
: GLWidget(parent)
{

}

GLWidget_Quadrocopter::~GLWidget_Quadrocopter()
{

}

//------------------------------------------//

void GLWidget_Quadrocopter::initializeGL()
{
    GLWidget::initializeGL();

    //------------------------------//

    Vector3 extendet(50,5,50);
    Transform base_trans(Vector3(0,-10,0));
    auto m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    auto  collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    MeshGenerator::CuboidDescriptor desc_base(extendet);
    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    base_mesh->setCollider(collider_base);
    m_CScene->AddComponent( base_mesh );

    //------------------------------//
}

void GLWidget_Quadrocopter::update_scene()
{
    GLWidget::update_scene();
}

void GLWidget_Quadrocopter::paintGL()
{
   GLWidget::paintGL();
}

//------------------------------------------//

void GLWidget_Quadrocopter::keyPressEvent(QKeyEvent *keyEvent)
{
    GLWidget::keyPressEvent(keyEvent);
}

void GLWidget_Quadrocopter::keyReleaseEvent(QKeyEvent *keyEvent)
{
    GLWidget::keyReleaseEvent(keyEvent);
}
