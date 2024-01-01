#ifndef ICOMPONENTMESH_H
#define ICOMPONENTMESH_H

#include <IEngineComponent/IComponents.hpp>


class IComponentMesh : public IComponentObject2
{
private:

    // Запрещаем копирование и присваивание экземпляра класса.
    IComponentMesh(const IComponentMesh&) = delete;
    IComponentMesh& operator=(const IComponentMesh&) = delete;

    public:

        IComponentMesh(IMesh *_mesh);

        //! Descriptor structure for a cuboid (also cube) mesh.
        IComponentMesh(const MeshGenerator::CuboidDescriptor& __descriptor_cuboid__);

        //! Descriptor structure for an ellispoid (also sphere) mesh.
        IComponentMesh(const MeshGenerator::EllipsoidDescriptor& __descriptor_Ellipsoid__) ;

        //! Descriptor structure for a cone mesh.
        IComponentMesh(const MeshGenerator::ConeDescriptor& __descriptor_Cone__) ;

        //! Descriptor structure for a cylinder mesh.
        IComponentMesh(const MeshGenerator::CylinderDescriptor& __descriptor_Cylinder__) ;

        //! Descriptor structure for a pie (also pie-diagram) mesh.
        IComponentMesh(const MeshGenerator::PieDescriptor& __descriptor_Pie__) ;

        //! Descriptor structure for a pipe mesh (i.e. cylinder with a hole).
        IComponentMesh(const MeshGenerator::PipeDescriptor& __descriptor_Pipe__) ;

        //! Descriptor structure for a capsule mesh (i.e. cylinder with a half-sphere at top and bottom).
        IComponentMesh(const MeshGenerator::CapsuleDescriptor& __descriptor_Capsule__) ;

        //! Descriptor structure for a torus mesh.
        IComponentMesh(const MeshGenerator::TorusDescriptor& __descriptor_Torus__) ;

        //! Descriptor structure for a torus-knot mesh (uses the curve generator).
        IComponentMesh(const MeshGenerator::TorusKnotDescriptor& __descriptor_TorusKnot__) ;

        //! Descriptor structure for a spiral mesh.
        IComponentMesh(const MeshGenerator::SpiralDescriptor& __descriptor_Spiral__) ;

        //! Descriptor structure for a curve mesh (as a rope along a given curve function).
        IComponentMesh(const MeshGenerator::CurveDescriptor&  __descriptor_Curve__) ;

        //! Descriptor structure for a Bezier patch mesh.
        IComponentMesh(const MeshGenerator::BezierPatchDescriptor& __descriptor_Bezier__) ;

        ///! Destructor
       ~IComponentMesh();


        IEngine::IMesh *Mesh() const;

    protected:

        IEngine::IMesh* m_Mesh;
};





//    ~IComponentMesh();

#endif // ICOMPONENTMESH_H
