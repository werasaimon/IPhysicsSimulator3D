#ifndef ICOMPONENTCONSTRAITJOINT_H
#define ICOMPONENTCONSTRAITJOINT_H

#include <IEngineComponent/IComponentObject.h>

class IPhysicsWorld;

//template <typename T>
class IComponentConstraitJoint : public IComponentObject2
{
 public:

    IComponentConstraitJoint(const rp3d::JointInfo& _joint_info, IPhysicsWorld *_world);

    template<class T> T* GetTypeJoint()
    {
       return dynamic_cast<T*>(m_ConstaraitJoint);
    }


 private:

    rp3d::Joint* m_ConstaraitJoint;
};

#endif // ICOMPONENTCONSTRAITJOINT_H
