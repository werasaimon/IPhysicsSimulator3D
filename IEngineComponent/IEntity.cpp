#include <IEngineComponent/IEntity.h>

IEntity::IEntity()
{
}

void IEntity::AddComponent(IComponentObject2 *_components_object_)
{
    m_Components.push_back(_components_object_);
}

std::vector<IComponentObject2 *> IEntity::Components() const
{
    return m_Components;
}
