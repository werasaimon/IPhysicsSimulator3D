#include "IComponentRigidBody.h"


IComponentRigidBody::IComponentRigidBody(reactphysics3d::RigidBody *_physicsRigidBody_)
  : m_PhysRigidBody(_physicsRigidBody_)
{
    this->SetTransform(converAddaptive(_physicsRigidBody_->getTransform()));
}

IComponentRigidBody::IComponentRigidBody(const Transform& transform,  IPhysicsWorld *_physWorld_)
{
    this->SetTransform(transform);
    m_PhysRigidBody = _physWorld_->PhysicsWorld()->createRigidBody(converAddaptive(transform));
}

void IComponentRigidBody::InitTypePhysics(const reactphysics3d::BodyType& type)
{
    m_PhysRigidBody->setType(type);
}

rp3d::RigidBody *IComponentRigidBody::PhysRigidBody() const
{
    return m_PhysRigidBody;
}

reactphysics3d::Collider *IComponentRigidBody::AddCollider(reactphysics3d::CollisionShape *collisionShape, const Transform &transform)
{
    return m_PhysRigidBody->addCollider(collisionShape, converAddaptive(transform) );
}
