#ifndef IPHYSICSCOMMON_H
#define IPHYSICSCOMMON_H

#include <IEngine/reactphysics3d/reactphysics3d.h>
#include <IEngineComponent/IPhysicsWorld.h>
#include <IEngine/imaths.hpp>

class IPhysicsCommon : public rp3d::PhysicsCommon
{
 public:

     IPhysicsCommon();

     IPhysicsWorld* CCreatePhysicsWorld(const rp3d::PhysicsWorld::WorldSettings& worldSettings = rp3d::PhysicsWorld::WorldSettings())
     {
         return (new IPhysicsWorld( createPhysicsWorld(worldSettings)));
     }

     rp3d::BoxShape* CCreateBoxShape(const Vector3& extent)
     {
         return this->createBoxShape(converAddaptive(extent * scalar(0.5f)));
     }

     rp3d::SphereShape* CCreateSpereShape(scalar _radius)
     {
         return this->createSphereShape(_radius * scalar(0.5f));
     }

     rp3d::CapsuleShape* CCreateCapsuleShape(scalar radius, scalar height)
     {
         return this->createCapsuleShape(radius,height);
     }

     rp3d::ConvexMeshShape* CCreateConvexMeshShape(rp3d::PolyhedronMesh* polyhedronMesh, const Vector3& scaling = Vector3(1,1,1))
     {
         return this->createConvexMeshShape(polyhedronMesh,converAddaptive(scaling));
     }

     rp3d::ConcaveMeshShape* CCreateConcaveMeshShape(rp3d::TriangleMesh* triangleMesh, const Vector3& scaling = Vector3(1, 1, 1))
     {
        return this->createConcaveMeshShape(triangleMesh,converAddaptive(scaling));
     }
};

#endif // IPHYSICSCOMMON_H
