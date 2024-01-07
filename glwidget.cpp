
#include <glwidget.h>
#include <IEngine/IGeometry/Mesh/IMeshGenerator.h>
#include <QMenu>
#include <OpenGL/OpenGLRender.h>
#include <QThread>
//#include <GL/freeglut.h>


using namespace IEngine;

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
    m_PhysicsWorld(nullptr)
{
    for (int i = 0; i < 256; ++i)
    {
        mKeys[i] = false;
    }
}

GLWidget::~GLWidget()
{

    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    doneCurrent();

}



void GLWidget::initializeGL()
{

    //    #ifdef __ANDROID__
    //    #elif defined(WIN32) || defined(__linux__)

    //        GLenum err = glewInit();
    //        if(err != GLEW_OK)
    //        {
    //            printf("%s",glewGetErrorString(err));
    //        }

    //    #endif

    initializeOpenGLFunctions();

    glClearColor(0.f,0.f,0.0f,1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mTimeStep = (1.f/60.f);

    // Use QBasicTimer because its faster than QTimer
    timer.start( 10 , this);


    //===================================//


    m_SceneDescriptor.m_IsDrawFill = false;
    m_SceneDescriptor.m_IsDrawLines = true;
    m_SceneDescriptor.m_IsDynamics = false;

    m_CScene = new IScene(m_SceneDescriptor);


    //-------------- Init Camera ----------------//

    m_CCamera = new IComponentCamera(new IQCamera);

    mWidth  = 600;
    mHeight = 400;

    float aspect = mWidth / mHeight;
    float zNear  = 1.0;
    float zFar   = 250;
    float fov    = 30.0;

    m_CCamera->InitPerspective(fov,aspect,zNear,zFar);

    Vector3 m_Eye = Vector3::Z * -50.f + Vector3::Y * 30.f + Vector3::X * -30.f;
    Vector3 m_At = Vector3::ZERO;
    Vector3 m_Up = Vector3::Y;

    m_CCamera->setCenter(m_At);
    m_CCamera->setEye(m_Eye);
    m_CCamera->setUp(m_Up);


    //---------------------------------------------------------//


    m_PhysWorldSettings.defaultPositionSolverNbIterations = 10;
    m_PhysWorldSettings.defaultVelocitySolverNbIterations = 10;
    m_PhysWorldSettings.gravity = converAddaptive(Vector3(0,-30,0));
   // m_PhysWorldSettings.gravity = converAddaptive(Vector3::ZERO);
    m_PhysicsWorld = createPhysicsWorld(m_PhysWorldSettings);


    //---------------------------------------------------------//
}


void GLWidget::resizeGL( int w , int h )
{
    mWidth  = w;
    mHeight = h;

    float aspect = mWidth / mHeight;
    float zNear  = 1.0;
    float zFar   = 1000;
    float fov    = 30.0;

    m_CCamera->InitPerspective(fov,aspect,zNear,zFar);
}



void GLWidget::paintGL()
{
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_CCamera->LookAt();
//    m_CCamera->Update();

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(m_CCamera->Camera()->ProjectionMatrix());

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(m_CCamera->Camera()->ViewMatrix());


    for (auto it : m_CScene->Components())
    {
        auto c_mesh = dynamic_cast<IComponentMesh*>(it);
        auto c_transform = c_mesh->GetTransformMatrixHierarchy();
        if(m_CScene->Descriptor().m_IsDynamics == true)
        {
            if(c_mesh->Collider())
            {
                c_mesh->Collider()->getLocalToWorldTransform().getOpenGLMatrix(c_transform);
            }
        }

        if(m_CScene->Descriptor().m_IsDrawLines)
        {
            if(it->Type() == TYPE_COMPONENT::MESH_MODEL)
            {
                glColor3f(1.f,1.f,1.f);
                OpenGLRender::DrawComponentMeshLine(c_mesh->Mesh(),c_transform);
            }
        }

        if(m_CScene->Descriptor().m_IsDrawFill)
        {
            if(it->Type() == TYPE_COMPONENT::MESH_MODEL)
            {
                glColor3f(0.3f,0.3f,0.3f);
                OpenGLRender::DrawComponentMeshFill(c_mesh->Mesh(), c_transform);
            }
        }
    }


    //---------------------------------------------------------------//

    //    int32_t n = m_PhysicsWorld->PhysicsWorld()->getNbRigidBodies();
    //    for (int i = 0; i < n; ++i)
    //    {
    //        auto body = m_PhysicsWorld->PhysicsWorld()->getRigidBody(i);
    //        auto center = body->getTransform().getPosition();


    //        int _n = body->getNbColliders();
    //        for (int j = 0; j < _n; ++j)
    //        {
    //            auto collider = body->getCollider(j);
    //            auto pos_local = collider->getLocalToWorldTransform().getPosition();

    //            glPushMatrix();
    //            glBegin(GL_LINES);
    //            glVertex3f(center.x,center.y,center.z);
    //            glVertex3f(pos_local.x,pos_local.y,pos_local.z);
    //            glEnd();
    //            glPopMatrix();
    //        }

    //        glPushMatrix();
    //        glTranslatef(center.x,center.y,center.z);
    //        glutSolidSphere( 0.25 , 10.0, 10.0);
    //        glPopMatrix();
    //    }

    //---------------------------------------------------------------//
}

void GLWidget::update_scene()
{
    if(m_CScene->Descriptor().m_IsDynamics)
    {

        if(m_PhysicsWorld)
        {
            m_PhysicsWorld->update(mTimeStep);;
        }

        //---------------------//

        m_CScene->Update();

    }


    /**

    //===============================================================//

    float coff_speed = 0.1;

    if(mKeys[Qt::Key_W])
    {
        m_CCamera->setEye(m_CCamera->Eye() + Vector3::Z * coff_speed);
    }

    if(mKeys[Qt::Key_S])
    {
        m_CCamera->setEye(m_CCamera->Eye() - Vector3::Z * coff_speed);
    }

    if(mKeys[Qt::Key_A])
    {
        m_CCamera->setEye(m_CCamera->Eye() + Vector3::X * coff_speed);
    }

    if(mKeys[Qt::Key_D])
    {
        m_CCamera->setEye(m_CCamera->Eye() - Vector3::X * coff_speed);
    }

    if(mKeys[Qt::Key_Q])
    {
        m_CCamera->setEye(m_CCamera->Eye() + Vector3::Y * coff_speed);
    }

    if(mKeys[Qt::Key_E])
    {
        m_CCamera->setEye(m_CCamera->Eye() - Vector3::Y * coff_speed);
    }

    if(mKeys[Qt::Key_P])
    {
        m_CScene->Descriptor().m_IsDynamics = !m_CScene->Descriptor().m_IsDynamics;
        QThread::msleep(10);
    }

    //===============================================================//

    /**/
}


void GLWidget::timerEvent(QTimerEvent *e)
{
    update_scene();
    update();
}


void GLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    qDebug() << keyEvent->key();
    mKeys[keyEvent->key()] = true;

}

void GLWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{
    qDebug() << keyEvent->key();
    mKeys[keyEvent->key()] = false;
    keyEvent->accept();
}


void GLWidget::wheelEvent(QWheelEvent *event)
{
    event->accept();
}


void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->button())
    {

    }

    control_mouse.mouseX = e->x();
    control_mouse.mouseY = e->y();
}

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    mMouseButton = e->button();
    control_mouse.mouseX = control_mouse.mouseOldX = e->x();
    control_mouse.mouseY = control_mouse.mouseOldY = e->y();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mMouseButton = e->button();
    control_mouse.mouseX = control_mouse.mouseOldX = e->x();
    control_mouse.mouseY = control_mouse.mouseOldY = e->y();
}


void GLWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
}

IPhysicsCommon* GLWidget::CPhysInstrument()
{
    return &m_CPhysInstrument;
}

IPhysicsWorld *GLWidget::CPhysicsWorld() const
{
    return m_PhysicsWorld;
}

IScene *GLWidget::CScene() const
{
    return m_CScene;
}
