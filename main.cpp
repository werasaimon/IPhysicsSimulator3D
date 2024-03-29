#include "mainwindow.h"
#include <QApplication>
#include <GL/freeglut.h>

int main(int argc, char *argv[])
{
    glutInit(&argc,argv);

    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}


//// Libraries
//#include <IEngine/reactphysics3d/reactphysics3d.h>
//#include <iostream>

//// ReactPhysics3D namespace
//using namespace reactphysics3d;

//// Main function
//int main(int argc, char** argv) {

//    // First you need to create the PhysicsCommon object. This is a factory module
//    // that you can use to create physics world and other objects. It is also responsible
//    // for logging and memory management
//    PhysicsCommon physicsCommon;

//    // Create a physics world
//    PhysicsWorld* world = physicsCommon.createPhysicsWorld();

//    // Create a rigid body in the world
//    Vector3 position(0, 20, 0);
//    Quaternion orientation = Quaternion::identity();
//    Transform transform(position, orientation);
//    RigidBody* body = world->createRigidBody(transform);

//    const decimal timeStep = 1.0f / 60.0f;

//    // Step the simulation a few steps
//    for (int i=0; i < 200; i++) {

//        world->update(timeStep);

//        // Get the updated position of the body
//        const Transform& transform = body->getTransform();
//        const Vector3& position = transform.getPosition();

//        // Display the position of the body
//        std::cout << "Body Position: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
//    }

//    return 0;
//}
