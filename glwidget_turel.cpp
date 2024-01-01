#include "glwidget_turel.h"

GLWidget_Turel::GLWidget_Turel(class QWidget *parent)
    : GLWidget(parent)
{


}

GLWidget_Turel::~GLWidget_Turel()
{

}

void GLWidget_Turel::initializeGL()
{
    GLWidget::initializeGL();

    //---------------------------------------------------//

    m_CScene->Descriptor().m_IsDrawLines = true;
    m_CScene->Descriptor().m_IsDrawFill = true;
    m_CScene->Descriptor().m_IsDynamics = true;

    //---------------------------------------------------//


    m_TripodDynamics = new TripodeDynamic(this);


    //---------------------------------------------------//

    Vector3 extendet(50,5,50);
    Transform base_trans(Vector3(0,-10,0));
    auto m_CRigidBody_Base = new IComponentRigidBody(base_trans,m_PhysicsWorld);
    auto  collider_base = m_CRigidBody_Base->AddCollider(m_CPhysInstrument.CCreateBoxShape(extendet));
    m_CRigidBody_Base->InitTypePhysics(rp3d::BodyType::STATIC);

    MeshGenerator::CuboidDescriptor desc_base(extendet);
    IComponentMesh *base_mesh = new IComponentMesh(desc_base);
    base_mesh->setCollider(collider_base);
    m_CScene->AddComponent( base_mesh );

    //---------------------------------------------------//

    control_angle = Vector3::ZERO;

}


void GLWidget_Turel::update_scene()
{
    GLWidget::update_scene();

    //------------------------------------//

    if(CScene()->Descriptor().m_IsDynamics == true)
    {
        m_TripodDynamics->Update();
    }

    //------------------------------------//

    if( mKeys[Qt::Key_B])
    {

      Vector3 extendet_fixed(1,1,1);
      Vector3 point_fixed = Vector3(0,10,0);
      Transform trans_fixed(point_fixed);
      auto RigidBody_Fixed = new IComponentRigidBody(trans_fixed,this->CPhysicsWorld());
      auto geometry_mesh_box_fixed = new IComponentMesh(MeshGenerator::CuboidDescriptor(extendet_fixed));
      auto collision_shape_box_fixed = this->CPhysInstrument()->CCreateBoxShape(extendet_fixed);
      geometry_mesh_box_fixed->SetTransform(trans_fixed);
      RigidBody_Fixed->AddCollider2(collision_shape_box_fixed , geometry_mesh_box_fixed);
      this->CScene()->AddComponent(geometry_mesh_box_fixed);

      RigidBody_Fixed->InitTypePhysics(rp3d::BodyType::STATIC);
    }


    //    if( mKeys[Qt::Key_V])
    //    {
    //      //m_TripodDynamics->Test1();
    //    }

    //    if( mKeys[Qt::Key_B])
    //    {
    //      m_TripodDynamics->Shot();
    //    }

    if( is_stabilizaton == true )
    {
      m_TripodDynamics->UpdateLQR(control_angle);
    }

    //=====================================================//


//    pos1 = a;
//    pos2 = b;

    //=====================================================//
}

void GLWidget_Turel::paintGL()
{
    GLWidget::paintGL();

    //------------------------//

    m_TripodDynamics->Draw();

    //------------------------//
}

void GLWidget_Turel::keyPressEvent(QKeyEvent *keyEvent)
{
    GLWidget::keyPressEvent(keyEvent);

    if(keyEvent->key() == Qt::Key_B)
    {
      m_TripodDynamics->Shot();
    }
}

void GLWidget_Turel::keyReleaseEvent(QKeyEvent *keyEvent)
{
   GLWidget::keyReleaseEvent(keyEvent);
}





