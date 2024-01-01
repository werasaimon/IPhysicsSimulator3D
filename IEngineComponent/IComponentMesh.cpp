#include "IComponentMesh.h"


IComponentMesh::IComponentMesh(IMesh *_mesh)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(std::move(_mesh))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::CuboidDescriptor &__descriptor_cuboid__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_cuboid__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::EllipsoidDescriptor &__descriptor_Ellipsoid__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Ellipsoid__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::ConeDescriptor &__descriptor_Cone__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Cone__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::CylinderDescriptor &__descriptor_Cylinder__)
  : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Cylinder__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::PieDescriptor &__descriptor_Pie__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Pie__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::PipeDescriptor &__descriptor_Pipe__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL), m_Mesh(new IMeshGenerate(__descriptor_Pipe__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::CapsuleDescriptor &__descriptor_Capsule__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Capsule__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::TorusDescriptor &__descriptor_Torus__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Torus__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::TorusKnotDescriptor &__descriptor_TorusKnot__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_TorusKnot__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::SpiralDescriptor &__descriptor_Spiral__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Spiral__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::CurveDescriptor &__descriptor_Curve__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Curve__))
{

}

IComponentMesh::IComponentMesh(const MeshGenerator::BezierPatchDescriptor &__descriptor_Bezier__)
    : IComponentObject2(TYPE_COMPONENT::MESH_MODEL),
    m_Mesh(new IMeshGenerate(__descriptor_Bezier__))
{

}

IComponentMesh::~IComponentMesh()
{
    if(m_Mesh)
    {
        delete m_Mesh;
        m_Mesh = nullptr;
    }
}

IEngine::IMesh *IComponentMesh::Mesh() const
{
    return m_Mesh;
}


