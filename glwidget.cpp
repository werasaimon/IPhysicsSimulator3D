
#include <glwidget.h>
#include <IEngine/IGeometry/Mesh/IMeshGenerator.h>
#include <QMenu>
#include <OpenGL/OpenGLRender.h>
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


    m_SceneDescriptor.m_IsDrawFill = true;
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
   // m_PhysWorldSettings.gravity = converAddaptive(Vector3::ZERO);
    m_PhysicsWorld = createPhysicsWorld(m_PhysWorldSettings);


    //---------------------------------------------------------//

//    rp3d::Vector3 position(0, 10, 0);
//    rp3d::Quaternion orientation = IEngine::converAddaptive(Quaternion::IDENTITY);
//    rp3d::Transform transform(position, orientation);
//    body = m_PhysicsWorld->createRigidBody(transform);

//    rp3d::Transform s_transform = IEngine::converAddaptive(Transform::Identity());
//    auto shapeBox = m_PhysicsCommon.createBoxShape(IEngine::converAddaptive(Vector3(2,2,2)));
//    auto collider_a = body->addCollider(shapeBox,s_transform);
//    body->setType(rp3d::BodyType::DYNAMIC);

//    MeshGenerator::CuboidDescriptor descp_dynamic(Vector3(2,2,2));
//    IComponentMesh *dynamic_mesh = new IComponentMesh(descp_dynamic);
//    dynamic_mesh->SetTransformMatrix(Matrix4::CreateTranslation(Vector3(0,2,0)));
//    m_CScene->AddComponent( dynamic_mesh );

//     m_ProxyCollider[collider_a] = dynamic_mesh;

    //---------------------------------------------------------//


    //     rp3d::Vector3 base_position(0, -10, 0);
    //     rp3d::Transform base_transform(base_position, IEngine::converAddaptive(Quaternion::IDENTITY));
    //     auto base_body = m_PhysicsWorld->createRigidBody(base_transform);

    //     auto base_shapeBox = m_PhysicsCommon.createBoxShape(IEngine::converAddaptive(Vector3(50,10,50)) );
    //     auto collider_b = base_body->addCollider(base_shapeBox,IEngine::converAddaptive(Transform::Identity()));

    //     MeshGenerator::CuboidDescriptor descp_base(Vector3(25,2,25));
    //     IComponentMesh *base_mesh = new IComponentMesh(descp_base);
    //     //base_mesh->SetTransformMatrix(Matrix4::CreateTranslation(Vector3(0,0,0)));
    //     m_CScene->AddComponent( base_mesh );

    //     base_body->setType(rp3d::BodyType::STATIC);

//    rp3d::Transform transform_base = rp3d::Transform::identity();
//    transform_base.setPosition(rp3d::Vector3(0,-20,0));
//    rp3d::RigidBody *physBase = m_PhysicsWorld->createRigidBody(transform_base);
//    auto collider_b = physBase->addCollider( m_PhysicsCommon.createBoxShape(rp3d::Vector3(50,10,50)),
//                                            rp3d::Transform::identity() );
//    physBase->setType(rp3d::BodyType::STATIC);

//    MeshGenerator::CuboidDescriptor descp(Vector3(25,2,25));
//    IComponentMesh *cuboid_mesh = new IComponentMesh(descp);
//    cuboid_mesh->SetTransformMatrix(Matrix4::CreateTranslation(Vector3(0,-20,0)));
//    m_CScene->AddComponent( cuboid_mesh );

//    m_ProxyCollider[collider_b] = base_mesh;

    //---------------------------------------------------------//

    //    Transform trans(Vector3(0,10,2));
    //    auto m_CRigidBody = new IComponentRigidBody(trans,m_PhysicsWorld);

    //    Vector3 extende(2,2,2);

    //    auto collision_shape = m_CPhysInstrument.CCreateBoxShape(extende);

    //    MeshGenerator::CuboidDescriptor descp_cubic(extende);
    //    IComponentMesh *cubic_mesh = new IComponentMesh(descp_cubic);
    //    cubic_mesh->SetTransform(Transform(Vector3(0,12,0)));
    //    m_CScene->AddComponent( cubic_mesh );
    //    m_CRigidBody->AddCollider2(collision_shape,cubic_mesh);


    //    MeshGenerator::CuboidDescriptor descp_cubic_2(extende);
    //    IComponentMesh *cubic_mesh_2 = new IComponentMesh(descp_cubic_2);
    //    cubic_mesh_2->SetTransform(Transform(Vector3(0,8,0)));
    //    m_CScene->AddComponent( cubic_mesh_2 );
    //    m_CRigidBody->AddCollider2(collision_shape,cubic_mesh_2);


    //    MeshGenerator::CuboidDescriptor descp_cubic_3(extende);
    //    IComponentMesh *cubic_mesh_3 = new IComponentMesh(descp_cubic_2);
    //    cubic_mesh_3->SetTransform(Transform(Vector3(0,10,5)));
    //    m_CScene->AddComponent( cubic_mesh_3 );
    //    auto coll = m_CRigidBody->AddCollider2(collision_shape,cubic_mesh_3);

    //    rp3d::Material materiall(0.3f,0.5f,50.f);
    //    coll->setMaterial(materiall);


    ////   m_CRigidBody->PhysRigidBody()->setMass(5.f);
    //    m_CRigidBody->InitTypePhysics(rp3d::BodyType::DYNAMIC);


                    //    Transform trans_1(Vector3(0,10,0));
                    //    auto m_CRigidBody_1 = createRigidBody(trans_1);

                    //    Vector3 extende_1(2,2,2);
                    //    MeshGenerator::CuboidDescriptor descp_cubic_1(extende_1);
                    //    IComponentMesh *cubic_mesh_1 = new IComponentMesh(descp_cubic_1);
                    //    cubic_mesh_1->SetTransform(trans_1);
                    //    m_CRigidBody_1->AddCollider2(m_CPhysInstrument.CCreateBoxShape(extende_1),cubic_mesh_1);
                    //    m_CRigidBody_1->InitTypePhysics(rp3d::BodyType::STATIC);

                    //    m_CScene->AddComponent( cubic_mesh_1 );


                    //    IComponentRigidBody* prevRigidBody = m_CRigidBody_1;

                    //    for(int i = 1; i < 10; ++i)
                    //    {

                    //        Transform trans_2(Vector3(2.5 * i,10,0));
                    //        auto m_CRigidBody_2 = createRigidBody(trans_2);

                    //        Vector3 extende_2(2,2,2);
                    //        MeshGenerator::CuboidDescriptor descp_cubic_2(extende_2);
                    //        IComponentMesh *cubic_mesh_2 = new IComponentMesh(descp_cubic_2);
                    //        cubic_mesh_2->SetTransform(trans_2);
                    //        m_CRigidBody_2->AddCollider2(m_CPhysInstrument.CCreateBoxShape(extende_2),cubic_mesh_2);
                    //        m_CRigidBody_2->InitTypePhysics(rp3d::BodyType::DYNAMIC);

                    //        m_CScene->AddComponent( cubic_mesh_2 );


                    //        rp3d::HingeJointInfo HingeJointInfo(prevRigidBody->PhysRigidBody(),
                    //                                            m_CRigidBody_2->PhysRigidBody(),
                    //                                            prevRigidBody->PhysRigidBody()->getTransform().getPosition(),
                    //                                            rp3d::Vector3(0,0,1));

                    //        m_PhysicsWorld->PhysicsWorld()->createJoint(HingeJointInfo);

                    //        prevRigidBody = m_CRigidBody_2;

                    //    }



        /**

        for(int i=0; i < 100; ++i)
        {
            Vector3 extendet(2,2,2);

            //-----------------------------------------------------------------//

            Transform trans(Vector3(0,10*i,0));
            auto m_CRigidBody = new IComponentRigidBody(trans,m_PhysicsWorld);

            rp3d::CollisionShape *collision_shape = nullptr;
            if(i%2==0)
            {
                collision_shape = m_CPhysInstrument.CCreateBoxShape(extendet);
            }
            else
            {
                collision_shape = m_CPhysInstrument.CCreateSpereShape(extendet.Length());
            }

            //-----------------------------------------------------------------//

           // auto collider = m_CRigidBody->AddCollider(collision_shape);

           // Transform identity = Transform::Identity();

            if(i%2==0)
            {
                MeshGenerator::CuboidDescriptor descp_cubic(extendet);
                IComponentMesh *cubic_mesh = new IComponentMesh(descp_cubic);
                cubic_mesh->SetTransform(trans);
                m_CRigidBody->AddCollider2(collision_shape,cubic_mesh);
                m_CScene->AddComponent( cubic_mesh );
            }
            else
            {
                MeshGenerator::EllipsoidDescriptor descp_ellips(extendet);
                IComponentMesh *ellips_mesh = new IComponentMesh(descp_ellips);
                ellips_mesh->SetTransform(trans);
                m_CRigidBody->AddCollider2(collision_shape,ellips_mesh);
                m_CScene->AddComponent( ellips_mesh );
            }

            m_CRigidBody->InitTypePhysics(rp3d::BodyType::DYNAMIC);

            //-----------------------------------------------------------------//
        }

        /**/

    //    Vector3 extendet(50,5,50);
    //    Transform base_trans(Vector3(0,-10,0));
    //    auto m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    //    auto  collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    //    m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    //    MeshGenerator::CuboidDescriptor desc_base(extendet);
    //    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    //    base_mesh->setCollider(collider_base);
    //    m_CScene->AddComponent( base_mesh );

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
    }

    //===============================================================//
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
