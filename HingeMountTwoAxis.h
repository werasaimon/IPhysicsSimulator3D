#ifndef HINGEMOUNTTWOAXIS_H
#define HINGEMOUNTTWOAXIS_H

#include <IEngineComponent/IComponents.hpp>
#include <Sensors/ISensors.hpp>
#include <OpenGL_Render_Interface.h>

#include <GL/freeglut.h>
#include <QDebug>

class GLWidget;

class HingeMountTwoAxis : public OpenGL_Render_Interface
{
public:

    HingeMountTwoAxis(GLWidget *_globalScene_ ,
                      IComponentRigidBody *body1,
                      IComponentRigidBody *body2,
                      const Vector3& _origin ,
                      const Vector3& _axis1,
                      const Vector3& _axis2);

    HingeMountTwoAxis(GLWidget *_globalScene_ ,
                      IComponentRigidBody *body1,
                      IComponentRigidBody *body2,
                      const Vector3& _origin1 ,
                      const Vector3& _origin2 ,
                      const Vector3& _axis1,
                      const Vector3& _axis2);

    void Draw();

    IComponentRigidBody *RigidBodyOuterPortion() const;

    IComponentConstraitJoint *GetHingeConstraintJoint1() const;
    IComponentConstraitJoint *GetHingeConstraintJoint2() const;

    Vector3 GetAnchorWorldPosition1() const;
    Vector3 GetAnchorWorldPosition2() const;

    Vector3 GetAxis1() const;
    Vector3 GetAxis2() const;

private:

    IComponentConstraitJoint *m_HingeConstraintJoint1;
    IComponentConstraitJoint *m_HingeConstraintJoint2;

    Vector3 m_AnchorWorldPosition1;
    Vector3 m_AnchorWorldPosition2;
    Vector3 m_Axis1;
    Vector3 m_Axis2;

    IComponentRigidBody *m_RigidBodyOuterPortion;


};

#endif // HINGEMOUNTTWOAXIS_H
