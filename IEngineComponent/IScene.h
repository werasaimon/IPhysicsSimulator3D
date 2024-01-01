#ifndef ISCENE_H
#define ISCENE_H

#include <IEngineComponent/IEntity.h>
#include <IEngine/reactphysics3d/reactphysics3d.h>

struct SceneDscriptor
{
    bool  m_IsDrawLines;
    bool  m_IsDrawFill;
    bool  m_IsDynamics;
};


class IScene : public IEntity
{
public:
    IScene(SceneDscriptor _Descriptor);

    void Setup() override;
    void Update() override;

    SceneDscriptor& Descriptor();

private:

    SceneDscriptor m_Descriptor;




};

#endif // ISCENE_H
