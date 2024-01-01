#include "IScene.h"


IScene::IScene(SceneDscriptor _Descriptor)
    : m_Descriptor(_Descriptor)
{

}

void IScene::Setup()
{

}

void IScene::Update()
{
    if(m_Descriptor.m_IsDynamics == true)
    {
        for( auto it : m_Components )
        {
            it->Update(1.f/60.f);
        }
    }
}

SceneDscriptor &IScene::Descriptor()
{
    return m_Descriptor;
}
