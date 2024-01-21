#include "glwidget_quadrocopter.h"
#include <GL/freeglut.h>
#include <QThread>

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

    mOpenGLRenderText.init("resources/fonts/ZenDots-Regular.ttf", 9/* size */);

    //------------------------------//

    Vector3 extendet(250,5,250);
    Transform base_trans(Vector3(0,-10,0));
    IComponentRigidBody* m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    rp3d::Collider* collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    MeshGenerator::CuboidDescriptor desc_base(extendet);
    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    base_mesh->setCollider(collider_base);
    m_CScene->AddComponent( base_mesh );

    //------------------------------//

    m_QuadroDynamica = new IQuadrocopterDynamica(this);

    //------------------------------//

    m_PositionStability = Vector3(0,10,0);

    //------------------------------//

    this->m_CScene->Descriptor().m_IsDrawFill = true;
    this->m_CScene->Descriptor().m_IsDrawLines = true;
    this->m_CScene->Descriptor().m_IsDynamics = false;

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

            auto physics_body_drone = m_QuadroDynamica->PhysicsBody_Base();
            Vector3 position_drone = physics_body_drone->GetTransform().GetPosition();
            m_CCamera->setCenter(position_drone);


            if(mKeys[Qt::Key_8]) { m_PositionStability += Vector3::Z * 0.1f; }
            if(mKeys[Qt::Key_2]) { m_PositionStability -= Vector3::Z * 0.1f; }
            if(mKeys[Qt::Key_4]) { m_PositionStability += Vector3::X * 0.1f; }
            if(mKeys[Qt::Key_6]) { m_PositionStability -= Vector3::X * 0.1f; }
            if(mKeys[Qt::Key_7]) { m_PositionStability += Vector3::Y * 0.1f; }
            if(mKeys[Qt::Key_9]) { m_PositionStability -= Vector3::Y * 0.1f; }
        }
    }


    // float coff_speed = 0.01;
    // if(mKeys[Qt::Key_W])
    // {
    //     m_CCamera->setEye(m_CCamera->Eye() + Vector3::Z * coff_speed);
    // }

    // if(mKeys[Qt::Key_S])
    // {
    //     m_CCamera->setEye(m_CCamera->Eye() - Vector3::Z * coff_speed);
    // }

    // if(mKeys[Qt::Key_P])
    // {
    //     m_CScene->Descriptor().m_IsDynamics = !m_CScene->Descriptor().m_IsDynamics;
    //     QThread::msleep(10);
    // }


}


void GLWidget_Quadrocopter::renderText()
{
    glPushMatrix();
    glLoadIdentity();
    glColor3f(0,1,0);

    static char buff[100];

    if(m_CScene->Descriptor().m_IsDynamics == true)
    {
        snprintf(&buff[0], sizeof(buff), "Physics Simulate : ON \n");
    }
    else
    {
        snprintf(&buff[0], sizeof(buff), "Physics Simulate : OFF \n");
    }

    mOpenGLRenderText.print( 20 /* xpos */, mHeight - 30 /* ypos */, buff);

    //--------------------------------------------------------------------------//

    snprintf(&buff[0], sizeof(buff), "set position:| X:%.2f | Y:%.2f | Z:%.2f \n",
              m_PositionStability.x,
              m_PositionStability.y,
              m_PositionStability.z);

    mOpenGLRenderText.print( 250 /* xpos */, mHeight - 30 /* ypos */, 0, buff);

    //--------------------------------------------------------------------------//

    Vector3 velocity = m_QuadroDynamica->PhysicsBody_Base()->GetLinearVelocity();
    buff[0] = {0};
    snprintf(&buff[0], sizeof(buff), "linear velocity:| X:%.2f | Y:%.2f | Z:%.2f \n",
    velocity.x,
    velocity.y,
    velocity.z);

    mOpenGLRenderText.print( 600 /* xpos */, mHeight - 30 /* ypos */, 0, buff);

    //--------------------------------------------------------------------------//

    Vector3 angular = m_QuadroDynamica->PhysicsBody_Base()->GetAngularVelocity();
    buff[0] = {0};
    snprintf(&buff[0], sizeof(buff), "angular velocity:| X:%.2f | Y:%.2f | Z:%.2f \n",
             angular.x,
             angular.y,
             angular.z);

    mOpenGLRenderText.print( 950 /* xpos */, mHeight - 30 /* ypos */, 0, buff);

    // //--------------------------------------------------------------------------//

    Vector3 position = m_QuadroDynamica->PhysicsBody_Base()->GetTransform().GetPosition();
    buff[0] = {0};
    snprintf(&buff[0], sizeof(buff), "Real Position:| X:%.2f | Y:%.2f | Z:%.2f \n",
             position.x,
             position.y,
             position.z);

    mOpenGLRenderText.print(  1350.f /* xpos */, mHeight - 30 /* ypos */ , buff);

    glPopMatrix();
}


void GLWidget_Quadrocopter::paintGL()
{
    GLWidget::paintGL();

    renderText();

    glPushMatrix();
    glTranslatef(m_PositionStability.x,
                 m_PositionStability.y,
                 m_PositionStability.z);
    glColor3f(1,0,0);
    glutSolidSphere(0.5, 20, 20);
    glColor3f(1,1,1);
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

void GLWidget_Quadrocopter::closeEvent(QCloseEvent *event)
{
    GLWidget::closeEvent(event);
    mOpenGLRenderText.clean();
    event->accept();
}

IQuadrocopterDynamica *GLWidget_Quadrocopter::QuadroDynamica() const
{
    return m_QuadroDynamica;
}
