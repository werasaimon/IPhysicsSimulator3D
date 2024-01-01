#include <IEngineComponent/IComponentConstraitJoint.h>
#include <IEngineComponent/IPhysicsWorld.h>

IComponentConstraitJoint::IComponentConstraitJoint(const reactphysics3d::JointInfo &_joint_info, IPhysicsWorld *_world)
{
    m_ConstaraitJoint = _world->PhysicsWorld()->createJoint(_joint_info);
}
