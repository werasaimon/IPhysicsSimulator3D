#include "glwidget_quadrocopter.h"
#include <GL/freeglut.h>

GLWidget_Quadrocopter::GLWidget_Quadrocopter(QWidget *parent)
: GLWidget(parent)
{
    for (int i = 0; i < 256; ++i)
    {
        mKeys[i] = false;
    }
}

GLWidget_Quadrocopter::~GLWidget_Quadrocopter()
{

}

//------------------------------------------//

void GLWidget_Quadrocopter::initializeGL()
{
    //------------------------------//

    GLWidget::initializeGL();

    //------------------------------//

    // Vector3 extendet(50,5,50);
    // Transform base_trans(Vector3(0,-10,0));
    // auto m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    // auto  collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    // m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    // MeshGenerator::CuboidDescriptor desc_base(extendet);
    // IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    // base_mesh->setCollider(collider_base);
    // m_CScene->AddComponent( base_mesh );

    //------------------------------//

    m_QuadroDynamica = new IQuadrocopterDynamica(this);

    //------------------------------//

    m_PositionStability = Vector3(0,10,0);

    //------------------------------//
}

void GLWidget_Quadrocopter::update_scene()
{
    GLWidget::update_scene();


    if( m_CScene->Descriptor().m_IsDynamics )
    {
        if(m_QuadroDynamica)
        {
            m_QuadroDynamica->UpdatePosition(m_PositionStability);
            //m_QuadroDynamica->UpdateAngle(m_AngleStability);
        }


        if(m_QuadroDynamica)
        {
            if(mKeys[Qt::Key_U]) m_PositionStability += Vector3::Y * 0.1f;
            if(mKeys[Qt::Key_I]) m_PositionStability -= Vector3::Z * 0.1f;
            if(mKeys[Qt::Key_J]) m_PositionStability += Vector3::X;
            if(mKeys[Qt::Key_K]) m_PositionStability -= Vector3::X;
        }
    }
}


void GLWidget_Quadrocopter::paintGL()
{
    GLWidget::paintGL();

    glPushMatrix();
    glTranslatef(m_PositionStability.x,
                 m_PositionStability.y,
                 m_PositionStability.z);
    glutSolidSphere(1.1, 20, 20);
    glPopMatrix();

    if(m_QuadroDynamica)
    {
        m_QuadroDynamica->RenderDebug();
    }
}

//------------------------------------------//

void GLWidget_Quadrocopter::keyPressEvent(QKeyEvent *keyEvent)
{
    GLWidget::keyPressEvent(keyEvent);
    keyEvent->accept();
}

void GLWidget_Quadrocopter::keyReleaseEvent(QKeyEvent *keyEvent)
{
    GLWidget::keyReleaseEvent(keyEvent);
    keyEvent->accept();
}
