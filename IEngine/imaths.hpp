#ifndef IMATHS_HPP
#define IMATHS_HPP

#include <IEngine/IMath/IFunc.h>
#include <IEngine/IMath/IVector2D.h>
#include <IEngine/IMath/IVector3D.h>
#include <IEngine/IMath/IVector4D.h>
#include <IEngine/IMath/ILorentzVector.h>
#include <IEngine/IMath/IMatrix.h>
#include <IEngine/IMath/IMatrix2x2.h>
#include <IEngine/IMath/IMatrix3x3.h>
#include <IEngine/IMath/IMatrix4x4.h>
#include <IEngine/IMath/IQuaternion.h>
#include <IEngine/IMath/IOctonion.h>
#include <IEngine/IMath/IComplex.h>
#include <IEngine/IMath/ITransform.h>
#include <IEngine/IMath/IAffineTransform.h>
#include <IEngine/IMath/ISpherical.h>

#include <IEngine/IMath/IVector.h>
#include <IEngine/IMath/IScalarType.h>
#include <IEngine/IMath/IAlgebra.h>

#include <limits>

#include <IEngine/reactphysics3d/reactphysics3d.h>


namespace IEngine
{
    typedef float scalar;

    typedef IMath::IVector2D<scalar>        Vector2;
    typedef IMath::IVector3D<scalar>        Vector3;
    typedef IMath::IVector4D<scalar>        Vector4;
    typedef IMath::ILorentzVector<scalar>   LorentzVector;
    typedef IMath::IMatrix2x2<scalar>       Matrix2;
    typedef IMath::IMatrix3x3<scalar>       Matrix3;
    typedef IMath::IMatrix4x4<scalar>       Matrix4;
    typedef IMath::IQuaternion<scalar>      Quaternion;
    typedef IMath::ITransform<scalar>       Transform;
    typedef IMath::IAffineTransform<scalar> AffineTransform;


    typedef IMath::IVector2D<int> Index2i;
    typedef IMath::IVector3D<int> Index3i;
    typedef IMath::IVector4D<int> Index4i;

    typedef IMath::IVector2D<int> Vector2i;
    typedef IMath::IVector3D<int> Vector3i;
    typedef IMath::IVector4D<int> Vector4i;

    const scalar DECIMAL_SMALLEST = -std::numeric_limits<scalar>::max();
    const scalar DECIMAL_LARGEST  =  std::numeric_limits<scalar>::max();


    static Vector3 converAddaptive(const rp3d::Vector3& pos)
    {
        return Vector3(pos.x,pos.y,pos.z);
    }

    static Quaternion converAddaptive(const rp3d::Quaternion& rot)
    {
        return Quaternion(rot.w,rot.x,rot.y,rot.z);
    }

    static Quaternion converAddaptive_Z(const rp3d::Quaternion& rot)
    {
        return Quaternion(rot.w,rot.x,rot.z,rot.y);
    }

    static Transform converAddaptive(const rp3d::Transform& trans)
    {
        return Transform( converAddaptive(trans.getPosition()),
                          converAddaptive(trans.getOrientation()));
    }

    static Matrix3 converAddaptive(const rp3d::Matrix3x3& mat)
    {
        return Matrix3(mat[0][0],mat[0][1],mat[0][2],
                       mat[1][0],mat[1][1],mat[1][2],
                       mat[2][0],mat[2][1],mat[2][2]);
    }


    static Matrix4 ConverAddaptiveTransformToMatrix4(const rp3d::Transform& transform)
    {
        Matrix4 res;
        transform.getOpenGLMatrix(res);
        return res;
    }



    //------------------------------------------------------------//

    static rp3d::Vector3 converAddaptive(const Vector3& pos)
    {
        return rp3d::Vector3(pos.x,pos.y,pos.z);
    }

    static rp3d::Quaternion converAddaptive(const Quaternion& rot)
    {
        return rp3d::Quaternion(rot._x(),rot._y(),rot._z(),rot._w());
    }

    static rp3d::Transform converAddaptive(const Transform& trans)
    {
        return rp3d::Transform( converAddaptive(trans.GetPosition()),
                                converAddaptive(trans.GetRotation()));
    }

    static rp3d::Matrix3x3 converAddaptive(const Matrix3& mat)
    {
        return rp3d::Matrix3x3(mat[0][0],mat[0][1],mat[0][2],
                               mat[1][0],mat[1][1],mat[1][2],
                               mat[2][0],mat[2][1],mat[2][2]);
    }


    //------------------------------------------------------------//



}




#endif // IMATHS_HPP
