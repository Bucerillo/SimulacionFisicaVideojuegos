#pragma once
#include <cmath>
#include <PxPhysicsAPI.h>

class Vector3D {
public:
    float x, y, z;

    Vector3D();                                     // Por defecto (0,0,0)
    Vector3D(float x, float y, float z);            // Por parámetros
    Vector3D(const physx::PxVec3& v);               // Conversión desde PhysX

    float magnitude() const;
    Vector3D normalize() const;

    float dot(const Vector3D& v) const;            // Producto escalar
    Vector3D cross(const Vector3D& v) const;        // Producto vectorial

    Vector3D& operator=(const Vector3D& v);
    Vector3D operator+(const Vector3D& v) const;
    Vector3D operator-(const Vector3D& v) const;
    Vector3D operator*(float scalar) const;
    friend Vector3D operator*(float scalar, const Vector3D& v);
    Vector3D& operator+=(const Vector3D& v);

    operator physx::PxVec3() const;
};