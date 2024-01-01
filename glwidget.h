#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QWheelEvent>
#include <QObject>
#include <QWidget>

#include <IEngine/reactphysics3d/reactphysics3d.h>
#include <IEngineComponent/IComponents.hpp>
#include <IEngineComponent/IScene.h>
#include <Sensors/ISensors.hpp>

using namespace IEngine;
using namespace IMath;


//struct SceneDscriptor
//{
//    float m_MainLightPower;
//    float m_ShadowPointCloudFilteringQuality; // качество теней, точность PointCloudFiltering
//    int   m_ShadowMapSize;                      // качество теней, размер карты теней;

//    bool  m_IsDrawShadow; // отрисовка теней
//    bool  m_IsDrawLines;
//    bool  m_IsDrawFill;
//    bool  m_IsDrawShader;

//    bool  m_onSimulateDynamics;

//};


class GLWidget : public QOpenGLWidget , protected QOpenGLFunctions //, public UnitKeyButton
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

public:

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void update_scene();


    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);

    virtual void timerEvent(QTimerEvent *e);
    virtual void wheelEvent(QWheelEvent *event);

    virtual void keyPressEvent( QKeyEvent *keyEvent);
    virtual void keyReleaseEvent( QKeyEvent *keyEvent);

    void closeEvent(QCloseEvent *event);

    void setText(QString str)
    {
        qDebug() << str;
    }

public:

    IPhysicsCommon *CPhysInstrument();
    IPhysicsWorld  *CPhysicsWorld() const;
    IScene *CScene() const;

protected:

    SceneDscriptor m_SceneDescriptor;

    //-----------------------------//

    // First you need to create the PhysicsCommon object. This is a factory module
    // that you can use to create physics world and other objects. It is also responsible
    // for logging and memory management
    //rp3d::PhysicsCommon m_PhysicsCommon;
    //rp3d::PhysicsWorld* m_PhysicsWorld;
    //rp3d::RigidBody* body;

    //std::map< rp3d::Collider* , IComponentObject2* > m_ProxyCollider;


    //-----------------------------//


    rp3d::PhysicsWorld::WorldSettings m_PhysWorldSettings;

    IPhysicsCommon m_CPhysInstrument;
    IPhysicsWorld *m_PhysicsWorld;

    //IComponentRigidBody *m_CRigidBody;
    //IComponentRigidBody *m_CRigidBody_Base;


    //-----------------------------//

  //  SceneDscriptor      m_SceneDscriptor;
  //  IQCamera            m_Camera;

    IScene*           m_CScene;
    IComponentCamera *m_CCamera;

    //-----------------------------//

    bool mKeys[256];
    int  mMouseButton;

    //-----------------------------//

    /// Basic timer
    QBasicTimer  timer;

    /// Update FPS time
    float mTimeStep;

    //-----------------------------//
    struct Mouse
    {
        float mouseOldX;
        float mouseOldY;

        float mouseX;
        float mouseY;

    }  control_mouse;


    float mWidth;
    float mHeight;

    //-----------------------------//

public:

    IPhysicsWorld* createPhysicsWorld(rp3d::PhysicsWorld::WorldSettings settings)
    {
        return m_CPhysInstrument.CCreatePhysicsWorld(settings);
    }

    IComponentRigidBody* createRigidBody(const Transform& transform)
    {
        return new IComponentRigidBody( transform , m_PhysicsWorld );
    }

    IComponentConstraitJoint* createJoint(const rp3d::JointInfo& _joint_info)
    {
        return  new IComponentConstraitJoint(_joint_info,m_PhysicsWorld);
    }



//    rp3d::Collider* createCollider(rp3d::CollisionShape* _collision_shpe, const Transform& transform)
//    {
//        return new rp3d::Collider(_collision_shpe,transform);
//    }

};

#endif // GLWIDGET_H
