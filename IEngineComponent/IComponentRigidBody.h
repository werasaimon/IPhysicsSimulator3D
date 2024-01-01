#ifndef ICOMPONENTRIGIDBODY_H
#define ICOMPONENTRIGIDBODY_H

#include <IEngineComponent/IComponentObject.h>
#include <IEngineComponent/IPhysicsWorld.h>
#include <IEngine/reactphysics3d/reactphysics3d.h>

class IComponentRigidBody : public IComponentObject2
{
public:

    IComponentRigidBody(rp3d::RigidBody *_physRigidBody_);
    IComponentRigidBody(const Transform &transform, IPhysicsWorld *_physWorld_);

    void InitTypePhysics(const reactphysics3d::BodyType &type);

    rp3d::RigidBody *PhysRigidBody() const;
    rp3d::Collider *AddCollider(rp3d::CollisionShape* collisionShape, const Transform& transform = Transform::Identity());

    rp3d::Collider *AddCollider2(rp3d::CollisionShape* collisionShape, IComponentObject2 *object, const Transform* transform = nullptr)
    {
        if(transform)
        {
            auto collider = m_PhysRigidBody->addCollider(collisionShape, converAddaptive(*transform) );
            object->setCollider(collider);
            return collider;
        }
        else
        {
            auto transform_local = this->GetTransformHierarchy().GetInverse() * object->GetTransformHierarchy();
            auto collider = m_PhysRigidBody->addCollider(collisionShape,  converAddaptive(transform_local));
            object->setCollider(collider);
            return collider;
        }
    }


    Transform GetTransform() const
    {
        return converAddaptive(m_PhysRigidBody->getTransform());
    }

    Vector3 GetLinearVelocity() const
    {
        return converAddaptive(m_PhysRigidBody->getLinearVelocity());
    }

    Vector3 GetAngularVelocity() const
    {
        return converAddaptive(m_PhysRigidBody->getAngularVelocity());
    }


    Vector3 getForce() const
    {
        return converAddaptive(m_PhysRigidBody->getForce());
    }

    // Return the total manually applied torque on the body (in world-space)
    /**
 * @return The total manually applied torque on the body (in world-space)
 */
    Vector3 getTorque() const
    {
        return converAddaptive(m_PhysRigidBody->getTorque());
    }


//    void Setup()
//    {

//    }

//    void Update(float elapsedTime)
//    {

//    }

private:

    rp3d::RigidBody *m_PhysRigidBody;
   // rp3d::PhysicsWorld *m_PhyssWorld;
};

#endif // ICOMPONENTRIGIDBODY_H
