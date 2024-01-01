#ifndef IPHYSICSWORLD_H
#define IPHYSICSWORLD_H

#include <IEngineComponent/IComponentObject.h>
#include <IEngine/reactphysics3d/reactphysics3d.h>

class IComponentRigidBody;

class IPhysicsWorld
{
public:

    IPhysicsWorld(rp3d::PhysicsWorld* _PhysicsWorld);

    rp3d::PhysicsWorld *PhysicsWorld();

    void update(scalar timeStep);


    void addNoCollisionPair(IComponentRigidBody* body1, IComponentRigidBody* body2);
    void addNoCollisionPair(reactphysics3d::CollisionBody *body1, reactphysics3d::CollisionBody *body2);

private:

    rp3d::PhysicsWorld* m_PhysicsWorld;
};

#endif // IPHYSICSWORLD_H
