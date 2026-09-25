#include "Vector3D.h"

// Constructores
Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3D::Vector3D(const physx::PxVec3& v) : x(v.x), y(v.y), z(v.z) {}

// Módulo: ||v|| = sqrt(x^2 + y^2 + z^2)
float Vector3D::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalización: v / ||v||
Vector3D Vector3D::normalize() const {
    float mag = magnitude();
    if (mag > 0.0f) {
        return Vector3D(x / mag, y / mag, z / mag);
    }
    return Vector3D(0.0f, 0.0f, 0.0f);
}

// Producto escalar: u . v = u.x*v.x + u.y*v.y + u.z*v.z
float Vector3D::dot(const Vector3D& v) const {
    return x * v.x + y * v.y + z * v.z;
}

// Producto vectorial: u x v
Vector3D Vector3D::cross(const Vector3D& v) const {
    return Vector3D(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

// Sobrecarga de operadores
Vector3D& Vector3D::operator=(const Vector3D& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v) const {
    return Vector3D(x + v.x, y + v.y, z + v.z);
}

Vector3D Vector3D::operator-(const Vector3D& v) const {
    return Vector3D(x - v.x, y - v.y, z - v.z);
}

Vector3D Vector3D::operator*(float scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D operator*(float scalar, const Vector3D& v) {
    return v * scalar;
}

Vector3D& Vector3D::operator+=(const Vector3D& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

// Conversión implícita/explícita a physx::PxVec3
Vector3D::operator physx::PxVec3() const {
    return physx::PxVec3(x, y, z);
}