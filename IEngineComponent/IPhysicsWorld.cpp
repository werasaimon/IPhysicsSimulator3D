#include <IEngineComponent/IPhysicsWorld.h>
#include <IEngineComponent/IComponentRigidBody.h>

IPhysicsWorld::IPhysicsWorld(reactphysics3d::PhysicsWorld *_PhysicsWorld)
    : m_PhysicsWorld(_PhysicsWorld)
{

}

rp3d::PhysicsWorld *IPhysicsWorld::PhysicsWorld()
{
    return m_PhysicsWorld;
}

void IPhysicsWorld::update(scalar timeStep)
{
    if(m_PhysicsWorld)
    {
        m_PhysicsWorld->update(timeStep);
    }
}

void IPhysicsWorld::addNoCollisionPair(IComponentRigidBody *body1, IComponentRigidBody *body2)
{
    m_PhysicsWorld->collisionDetection()->addNoCollisionPair(body1->PhysRigidBody()->getEntity(),
                                                             body2->PhysRigidBody()->getEntity());
}

void IPhysicsWorld::addNoCollisionPair(reactphysics3d::CollisionBody *body1, reactphysics3d::CollisionBody *body2)
{
    m_PhysicsWorld->collisionDetection()->addNoCollisionPair(body1->getEntity(),
                                                             body2->getEntity());
}
