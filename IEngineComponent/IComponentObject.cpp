#include "IComponentObject.h"

IComponentObject2::IComponentObject2(TYPE_COMPONENT _type)
    : IHierarchyTransform(0),
    m_Type(_type) ,
    m_Collider(nullptr)
{

}

rp3d::Collider *IComponentObject2::Collider() const
{
    return m_Collider;
}

void IComponentObject2::setCollider(rp3d::Collider *newCollider)
{
    m_Collider = newCollider;
}

TYPE_COMPONENT IComponentObject2::Type() const
{
    return m_Type;
}
