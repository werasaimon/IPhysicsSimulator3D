#ifndef IENTITY_H
#define IENTITY_H

#include "IHierarchy/IHierarchy/IHierarchyScene.h"
#include <IEngine/imaths.hpp>
#include <IEngine/engine.hpp>
#include <IEngineComponent/IComponents.hpp>

using namespace IEngine;
using namespace IMath;

class IEntity : public IHierarchyScene
{

private:
    // Запрещаем копирование и присваивание экземпляра класса.
    IEntity(const IEntity&) = delete;
    IEntity& operator=(const IEntity&) = delete;

public:
    IEntity();

    virtual void Setup(){}
    virtual void Update(){}

    //=========================================//

    void AddComponent(IComponentObject2* _components_object_);

    //========================================//

    std::vector<IComponentObject2 *> Components() const;

    //========================================//

protected:

    std::vector<IComponentObject2*> m_Components;

};

#endif // IENTITY_H
