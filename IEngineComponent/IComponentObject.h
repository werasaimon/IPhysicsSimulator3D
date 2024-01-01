#ifndef ICOMPONENTOBJECT_H
#define ICOMPONENTOBJECT_H

#include <IEngine/imaths.hpp>
#include <IEngine/engine.hpp>
#include <IEngine/reactphysics3d/reactphysics3d.h>

using namespace IEngine;
using namespace IMath;


enum struct TYPE_COMPONENT { DEFAULT , MESH_MODEL , CAMERA , LIGHT };

class IComponentObject2 : public IHierarchyTransform
{
    private:

        // Запрещаем копирование и присваивание экземпляра класса.
        IComponentObject2(const IComponentObject2&) = delete;
        IComponentObject2& operator=(const IComponentObject2&) = delete;

    public:

        TYPE_COMPONENT Type() const;

        rp3d::Collider *Collider() const;

        void setCollider(rp3d::Collider *newCollider);


//        virtual void Update(float elapsedTime)
//        {
//            if(m_Collider)
//            {
//                SetTransform( converAddaptive(m_Collider->getLocalToWorldTransform()) );
//            }
//        }

    protected:

        IComponentObject2(TYPE_COMPONENT _type = TYPE_COMPONENT::DEFAULT);


    private:

        TYPE_COMPONENT  m_Type;
        rp3d::Collider *m_Collider;


};


#endif // ICOMPONENTOBJECT_H
