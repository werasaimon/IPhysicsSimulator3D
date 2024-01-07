QT       += core gui opengl openglwidgets charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
#QMAKE_CXXFLAGS += -m32

# LIBS += -L/usr/local/lib -lSDL2
# LIBS += -L/usr/local/lib -lSDL2 -ldl -lpthread
# INCLUDEPATH += /usr/local/include

CONFIG += resources_big
DEFINES += ENABLE_STL_SUPPORT

#Linux
linux: {

#Android
 android: {
  LIBS +=  -lGLESv1_CM -lGLESv2
}

#Linux default
 !android: {
   LIBS += -lGL -lGLU -lglut #-lGLEW
}

}

#Windows
win32: {
   LIBS += -lopengl32 -lglu32  #-lglew32
}

#Windows
win64: {
   LIBS += -lopengl32 -lglu32  #-lglew32
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD/IEngine

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IEngine/ICommon/IColor.cpp \
    IEngine/IGeometry/IAABBox3D.cpp \
    IEngine/IGeometry/ILight.cpp \
    IEngine/IGeometry/IMateriall.cpp \
    IEngine/IGeometry/IQCamera.cpp \
    IEngine/IGeometry/IRect2D.cpp \
    IEngine/IGeometry/Mesh/IMesh.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorBezierPatch.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorCapsule.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorCone.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorCuboid.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorCurve.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorCylinder.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorDetails.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorEllipsoid.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorPie.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorPipe.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorSpiral.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorTorus.cpp \
    IEngine/IGeometry/Mesh/IMeshGeneratorTorusKnot.cpp \
    IEngine/IGeometry/Mesh/IMeshLoader.cpp \
    IEngine/IGeometry/Segments/ILine3D.cpp \
    IEngine/IGeometry/Segments/ILineSegment3D.cpp \
    IEngine/IGeometry/Segments/IPlane.cpp \
    IEngine/IGeometry/Segments/IRay.cpp \
    IEngine/IHierarchy/IHierarchy/IHierarchyNode.cpp \
    IEngine/IHierarchy/IHierarchy/IHierarchyScene.cpp \
    IEngine/IHierarchy/IHierarchyTransform.cpp \
    IEngine/reactphysics3d/body/CollisionBody.cpp \
    IEngine/reactphysics3d/body/RigidBody.cpp \
    IEngine/reactphysics3d/collision/Collider.cpp \
    IEngine/reactphysics3d/collision/CollisionCallback.cpp \
    IEngine/reactphysics3d/collision/ContactManifold.cpp \
    IEngine/reactphysics3d/collision/HalfEdgeStructure.cpp \
    IEngine/reactphysics3d/collision/OverlapCallback.cpp \
    IEngine/reactphysics3d/collision/PolygonVertexArray.cpp \
    IEngine/reactphysics3d/collision/PolyhedronMesh.cpp \
    IEngine/reactphysics3d/collision/RaycastInfo.cpp \
    IEngine/reactphysics3d/collision/TriangleMesh.cpp \
    IEngine/reactphysics3d/collision/TriangleVertexArray.cpp \
    IEngine/reactphysics3d/collision/broadphase/DynamicAABBTree.cpp \
    IEngine/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/CollisionDispatch.cpp \
    IEngine/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.cpp \
    IEngine/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.cpp \
    IEngine/reactphysics3d/collision/narrowphase/NarrowPhaseInput.cpp \
    IEngine/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.cpp \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.cpp \
    IEngine/reactphysics3d/collision/shapes/AABB.cpp \
    IEngine/reactphysics3d/collision/shapes/BoxShape.cpp \
    IEngine/reactphysics3d/collision/shapes/CapsuleShape.cpp \
    IEngine/reactphysics3d/collision/shapes/CollisionShape.cpp \
    IEngine/reactphysics3d/collision/shapes/ConcaveMeshShape.cpp \
    IEngine/reactphysics3d/collision/shapes/ConcaveShape.cpp \
    IEngine/reactphysics3d/collision/shapes/ConvexMeshShape.cpp \
    IEngine/reactphysics3d/collision/shapes/ConvexPolyhedronShape.cpp \
    IEngine/reactphysics3d/collision/shapes/ConvexShape.cpp \
    IEngine/reactphysics3d/collision/shapes/HeightFieldShape.cpp \
    IEngine/reactphysics3d/collision/shapes/SphereShape.cpp \
    IEngine/reactphysics3d/collision/shapes/TriangleShape.cpp \
    IEngine/reactphysics3d/components/BallAndSocketJointComponents.cpp \
    IEngine/reactphysics3d/components/ColliderComponents.cpp \
    IEngine/reactphysics3d/components/CollisionBodyComponents.cpp \
    IEngine/reactphysics3d/components/Components.cpp \
    IEngine/reactphysics3d/components/FixedJointComponents.cpp \
    IEngine/reactphysics3d/components/HingeJointComponents.cpp \
    IEngine/reactphysics3d/components/JointComponents.cpp \
    IEngine/reactphysics3d/components/RigidBodyComponents.cpp \
    IEngine/reactphysics3d/components/SliderJointComponents.cpp \
    IEngine/reactphysics3d/components/TransformComponents.cpp \
    IEngine/reactphysics3d/constraint/BallAndSocketJoint.cpp \
    IEngine/reactphysics3d/constraint/ContactPoint.cpp \
    IEngine/reactphysics3d/constraint/FixedJoint.cpp \
    IEngine/reactphysics3d/constraint/HingeJoint.cpp \
    IEngine/reactphysics3d/constraint/Joint.cpp \
    IEngine/reactphysics3d/constraint/SliderJoint.cpp \
    IEngine/reactphysics3d/engine/Entity.cpp \
    IEngine/reactphysics3d/engine/EntityManager.cpp \
    IEngine/reactphysics3d/engine/Island.cpp \
    IEngine/reactphysics3d/engine/Material.cpp \
    IEngine/reactphysics3d/engine/OverlappingPairs.cpp \
    IEngine/reactphysics3d/engine/PhysicsCommon.cpp \
    IEngine/reactphysics3d/engine/PhysicsWorld.cpp \
    IEngine/reactphysics3d/mathematics/Matrix2x2.cpp \
    IEngine/reactphysics3d/mathematics/Matrix3x3.cpp \
    IEngine/reactphysics3d/mathematics/Quaternion.cpp \
    IEngine/reactphysics3d/mathematics/Transform.cpp \
    IEngine/reactphysics3d/mathematics/Vector2.cpp \
    IEngine/reactphysics3d/mathematics/Vector3.cpp \
    IEngine/reactphysics3d/memory/HeapAllocator.cpp \
    IEngine/reactphysics3d/memory/MemoryManager.cpp \
    IEngine/reactphysics3d/memory/PoolAllocator.cpp \
    IEngine/reactphysics3d/memory/SingleFrameAllocator.cpp \
    IEngine/reactphysics3d/systems/BroadPhaseSystem.cpp \
    IEngine/reactphysics3d/systems/CollisionDetectionSystem.cpp \
    IEngine/reactphysics3d/systems/ConstraintSolverSystem.cpp \
    IEngine/reactphysics3d/systems/ContactSolverSystem.cpp \
    IEngine/reactphysics3d/systems/DynamicsSystem.cpp \
    IEngine/reactphysics3d/systems/SolveBallAndSocketJointSystem.cpp \
    IEngine/reactphysics3d/systems/SolveFixedJointSystem.cpp \
    IEngine/reactphysics3d/systems/SolveHingeJointSystem.cpp \
    IEngine/reactphysics3d/systems/SolveSliderJointSystem.cpp \
    IEngine/reactphysics3d/utils/DebugRenderer.cpp \
    IEngine/reactphysics3d/utils/DefaultLogger.cpp \
    IEngine/reactphysics3d/utils/Profiler.cpp \
    IEngineComponent/IComponentCamera.cpp \
    IEngineComponent/IComponentConstraitJoint.cpp \
    IEngineComponent/IComponentMesh.cpp \
    IEngineComponent/IComponentObject.cpp \
    IEngineComponent/IComponentRigidBody.cpp \
    IEngineComponent/IEntity.cpp \
    IEngineComponent/IPhysicsCommon.cpp \
    IEngineComponent/IPhysicsWorld.cpp \
    IEngineComponent/IScene.cpp \
    IQuadrocopterDynamica.cpp \
    OpenGL/OpenGLRender.cpp \
    OpenGL/geometry_opengl.cpp \
    OpenGL_Render_Interface.cpp \
    Sensors/IEncoderSensor.cpp \
    Sensors/IOrientationSensor.cpp \
    Sensors/IVirtualOrientationSensor.cpp \
    chart_widget.cpp \
    glwidget.cpp \
    glwidget_quadrocopter.cpp \
    main.cpp \
    mainwindow.cpp \


HEADERS += \
    IEngine/ICommon/IBernsteinPolynomial.h \
    IEngine/ICommon/IBezierPatch.h \
    IEngine/ICommon/IColor.h \
    IEngine/ICommon/IMemory/IList.h \
    IEngine/ICommon/IMemory/IMem.h \
    IEngine/ICommon/IMemory/IPair.h \
    IEngine/ICommon/IMemory/IStack.h \
    IEngine/ICommon/ISettings.h \
    IEngine/IGeometry/IAABBox3D.h \
    IEngine/IGeometry/ILight.h \
    IEngine/IGeometry/IMateriall.h \
    IEngine/IGeometry/IQCamera.h \
    IEngine/IGeometry/IRect2D.h \
    IEngine/IGeometry/Mesh/IIndexUtil.h \
    IEngine/IGeometry/Mesh/IMesh.h \
    IEngine/IGeometry/Mesh/IMeshGenerator.h \
    IEngine/IGeometry/Mesh/IMeshGeneratorDetails.h \
    IEngine/IGeometry/Mesh/IMeshLoader.h \
    IEngine/IGeometry/Mesh/ITypes.h \
    IEngine/IGeometry/Mesh/memory/dvector.h \
    IEngine/IGeometry/Mesh/memory/iterator_util.h \
    IEngine/IGeometry/Mesh/memory/refcount_vector.h \
    IEngine/IGeometry/Mesh/memory/small_list_set.h \
    IEngine/IGeometry/Segments/ILine3D.h \
    IEngine/IGeometry/Segments/ILineSegment3D.h \
    IEngine/IGeometry/Segments/IPlane.h \
    IEngine/IGeometry/Segments/IRay.h \
    IEngine/IHierarchy/IHierarchy/IHierarchyNode.h \
    IEngine/IHierarchy/IHierarchy/IHierarchyScene.h \
    IEngine/IHierarchy/IHierarchyTransform.h \
    IEngine/IMath/IAffineTransform.h \
    IEngine/IMath/IAlgebra.h \
    IEngine/IMath/IComplex.h \
    IEngine/IMath/IFunc.h \
    IEngine/IMath/ILorentzVector.h \
    IEngine/IMath/IMatrix.h \
    IEngine/IMath/IMatrix2x2.h \
    IEngine/IMath/IMatrix3x3.h \
    IEngine/IMath/IMatrix4x4.h \
    IEngine/IMath/IOctonion.h \
    IEngine/IMath/IQuaternion.h \
    IEngine/IMath/IReal.h \
    IEngine/IMath/IScalarType.h \
    IEngine/IMath/ISpherical.h \
    IEngine/IMath/ITransform.h \
    IEngine/IMath/IVector.h \
    IEngine/IMath/IVector2D.h \
    IEngine/IMath/IVector3D.h \
    IEngine/IMath/IVector4D.h \
    IEngine/IMath/IVectorType.h \
    IEngine/engine.hpp \
    IEngine/imaths.hpp \
    IEngine/reactphysics3d/body/CollisionBody.h \
    IEngine/reactphysics3d/body/RigidBody.h \
    IEngine/reactphysics3d/collision/Collider.h \
    IEngine/reactphysics3d/collision/CollisionCallback.h \
    IEngine/reactphysics3d/collision/ContactManifold.h \
    IEngine/reactphysics3d/collision/ContactManifoldInfo.h \
    IEngine/reactphysics3d/collision/ContactPair.h \
    IEngine/reactphysics3d/collision/ContactPointInfo.h \
    IEngine/reactphysics3d/collision/HalfEdgeStructure.h \
    IEngine/reactphysics3d/collision/OverlapCallback.h \
    IEngine/reactphysics3d/collision/PolygonVertexArray.h \
    IEngine/reactphysics3d/collision/PolyhedronMesh.h \
    IEngine/reactphysics3d/collision/RaycastInfo.h \
    IEngine/reactphysics3d/collision/TriangleMesh.h \
    IEngine/reactphysics3d/collision/TriangleVertexArray.h \
    IEngine/reactphysics3d/collision/broadphase/DynamicAABBTree.h \
    IEngine/reactphysics3d/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/CollisionDispatch.h \
    IEngine/reactphysics3d/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/GJK/GJKAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/GJK/VoronoiSimplex.h \
    IEngine/reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/NarrowPhaseInfoBatch.h \
    IEngine/reactphysics3d/collision/narrowphase/NarrowPhaseInput.h \
    IEngine/reactphysics3d/collision/narrowphase/SAT/SATAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsCapsuleAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h \
    IEngine/reactphysics3d/collision/narrowphase/SphereVsSphereAlgorithm.h \
    IEngine/reactphysics3d/collision/shapes/AABB.h \
    IEngine/reactphysics3d/collision/shapes/BoxShape.h \
    IEngine/reactphysics3d/collision/shapes/CapsuleShape.h \
    IEngine/reactphysics3d/collision/shapes/CollisionShape.h \
    IEngine/reactphysics3d/collision/shapes/ConcaveMeshShape.h \
    IEngine/reactphysics3d/collision/shapes/ConcaveShape.h \
    IEngine/reactphysics3d/collision/shapes/ConvexMeshShape.h \
    IEngine/reactphysics3d/collision/shapes/ConvexPolyhedronShape.h \
    IEngine/reactphysics3d/collision/shapes/ConvexShape.h \
    IEngine/reactphysics3d/collision/shapes/HeightFieldShape.h \
    IEngine/reactphysics3d/collision/shapes/SphereShape.h \
    IEngine/reactphysics3d/collision/shapes/TriangleShape.h \
    IEngine/reactphysics3d/components/BallAndSocketJointComponents.h \
    IEngine/reactphysics3d/components/ColliderComponents.h \
    IEngine/reactphysics3d/components/CollisionBodyComponents.h \
    IEngine/reactphysics3d/components/Components.h \
    IEngine/reactphysics3d/components/FixedJointComponents.h \
    IEngine/reactphysics3d/components/HingeJointComponents.h \
    IEngine/reactphysics3d/components/JointComponents.h \
    IEngine/reactphysics3d/components/RigidBodyComponents.h \
    IEngine/reactphysics3d/components/SliderJointComponents.h \
    IEngine/reactphysics3d/components/TransformComponents.h \
    IEngine/reactphysics3d/configuration.h \
    IEngine/reactphysics3d/constraint/BallAndSocketJoint.h \
    IEngine/reactphysics3d/constraint/ContactPoint.h \
    IEngine/reactphysics3d/constraint/FixedJoint.h \
    IEngine/reactphysics3d/constraint/HingeJoint.h \
    IEngine/reactphysics3d/constraint/Joint.h \
    IEngine/reactphysics3d/constraint/SliderJoint.h \
    IEngine/reactphysics3d/containers/Array.h \
    IEngine/reactphysics3d/containers/Deque.h \
    IEngine/reactphysics3d/containers/LinkedList.h \
    IEngine/reactphysics3d/containers/Map.h \
    IEngine/reactphysics3d/containers/Pair.h \
    IEngine/reactphysics3d/containers/Set.h \
    IEngine/reactphysics3d/containers/Stack.h \
    IEngine/reactphysics3d/containers/containers_common.h \
    IEngine/reactphysics3d/decimal.h \
    IEngine/reactphysics3d/engine/Entity.h \
    IEngine/reactphysics3d/engine/EntityManager.h \
    IEngine/reactphysics3d/engine/EventListener.h \
    IEngine/reactphysics3d/engine/Island.h \
    IEngine/reactphysics3d/engine/Islands.h \
    IEngine/reactphysics3d/engine/Material.h \
    IEngine/reactphysics3d/engine/OverlappingPairs.h \
    IEngine/reactphysics3d/engine/PhysicsCommon.h \
    IEngine/reactphysics3d/engine/PhysicsWorld.h \
    IEngine/reactphysics3d/mathematics/Matrix2x2.h \
    IEngine/reactphysics3d/mathematics/Matrix3x3.h \
    IEngine/reactphysics3d/mathematics/Quaternion.h \
    IEngine/reactphysics3d/mathematics/Ray.h \
    IEngine/reactphysics3d/mathematics/Transform.h \
    IEngine/reactphysics3d/mathematics/Vector2.h \
    IEngine/reactphysics3d/mathematics/Vector3.h \
    IEngine/reactphysics3d/mathematics/mathematics.h \
    IEngine/reactphysics3d/mathematics/mathematics_common.h \
    IEngine/reactphysics3d/mathematics/mathematics_functions.h \
    IEngine/reactphysics3d/memory/DefaultAllocator.h \
    IEngine/reactphysics3d/memory/HeapAllocator.h \
    IEngine/reactphysics3d/memory/MemoryAllocator.h \
    IEngine/reactphysics3d/memory/MemoryManager.h \
    IEngine/reactphysics3d/memory/PoolAllocator.h \
    IEngine/reactphysics3d/memory/SingleFrameAllocator.h \
    IEngine/reactphysics3d/reactphysics3d.h \
    IEngine/reactphysics3d/systems/BroadPhaseSystem.h \
    IEngine/reactphysics3d/systems/CollisionDetectionSystem.h \
    IEngine/reactphysics3d/systems/ConstraintSolverSystem.h \
    IEngine/reactphysics3d/systems/ContactSolverSystem.h \
    IEngine/reactphysics3d/systems/DynamicsSystem.h \
    IEngine/reactphysics3d/systems/SolveBallAndSocketJointSystem.h \
    IEngine/reactphysics3d/systems/SolveFixedJointSystem.h \
    IEngine/reactphysics3d/systems/SolveHingeJointSystem.h \
    IEngine/reactphysics3d/systems/SolveSliderJointSystem.h \
    IEngine/reactphysics3d/utils/DebugRenderer.h \
    IEngine/reactphysics3d/utils/DefaultLogger.h \
    IEngine/reactphysics3d/utils/Logger.h \
    IEngine/reactphysics3d/utils/Profiler.h \
    IEngineComponent/IComponentCamera.h \
    IEngineComponent/IComponentConstraitJoint.h \
    IEngineComponent/IComponentMesh.h \
    IEngineComponent/IComponentObject.h \
    IEngineComponent/IComponentRigidBody.h \
    IEngineComponent/IComponents.hpp \
    IEngineComponent/IEntity.h \
    IEngineComponent/IPhysicsCommon.h \
    IEngineComponent/IPhysicsWorld.h \
    IEngineComponent/IScene.h \
    IQuadrocopterDynamica.h \
    OpenGL/OpenGLRender.h \
    OpenGL/geometry_opengl.h \
    OpenGL_Render_Interface.h \
    Sensors/IEncoderSensor.h \
    Sensors/IOrientationSensor.h \
    Sensors/ISensors.hpp \
    Sensors/IVirtualOrientationSensor.h \
    chart_widget.h \
    glwidget.h \
    glwidget_quadrocopter.h \
    mainwindow.h \


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
