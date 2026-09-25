#include "P0S_Scene.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"

void P0S_Scene::init() {
    // ---------------------------------------------------------------------
    // ACTIVIDAD 3: Esfera en el origen (0,0,0)
    // ---------------------------------------------------------------------
    auto originSphere = new RenderItem(
        CreateShape(physx::PxSphereGeometry(1.0f)),
        new physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f)),
        Vector4(1.0f, 1.0f, 1.0f, 1.0f) // Blanco
    );
    renderItems.push_back(originSphere);

    // ---------------------------------------------------------------------
    // ACTIVIDAD 4 - RETO A: Sistema de Referencia Local (Producto Vectorial)
    // ---------------------------------------------------------------------
    Vector3D u(3.0f, 1.0f, 0.0f); // Eje local X
    Vector3D v(0.0f, 4.0f, 0.0f); // Eje local Y
    Vector3D w = u.cross(v);      // Vector perpendicular (Eje Z)

    Vector3D posX = u.normalize() * 5.0f;
    Vector3D posY = v.normalize() * 5.0f;
    Vector3D posZ = w.normalize() * 5.0f;

    auto itemX = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5f)), new physx::PxTransform(posX), Vector4(1.0f, 0.0f, 0.0f, 1.0f)); // Rojo
    auto itemY = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5f)), new physx::PxTransform(posY), Vector4(0.0f, 1.0f, 0.0f, 1.0f)); // Verde
    auto itemZ = new RenderItem(CreateShape(physx::PxSphereGeometry(0.5f)), new physx::PxTransform(posZ), Vector4(0.0f, 0.0f, 1.0f, 1.0f)); // Azul

    renderItems.push_back(itemX);
    renderItems.push_back(itemY);
    renderItems.push_back(itemZ);

    // ---------------------------------------------------------------------
    // ACTIVIDAD 4 - RETO B: Campo de Visión (Producto Escalar)
    // ---------------------------------------------------------------------
    Vector3D D(0.0f, 0.0f, 1.0f);
    Vector3D targets[4] = {
        Vector3D(2.0f, 0.0f, 3.0f),   // P_1
        Vector3D(-4.0f, 0.0f, 1.0f),  // P_2
        Vector3D(0.0f, 0.0f, -5.0f),  // P_3
        Vector3D(3.0f, 0.0f, 0.0f)    // P_4
    };

    for (int i = 0; i < 4; ++i) {
        float dotProduct = D.dot(targets[i]);
        Vector4 color;

        if (dotProduct > 0.0001f) {
            color = Vector4(0.0f, 1.0f, 0.0f, 1.0f); // VERDE: ángulo < 90°
        }
        else if (dotProduct < -0.0001f) {
            color = Vector4(1.0f, 0.0f, 0.0f, 1.0f); // ROJO: ángulo > 90°
        }
        else {
            color = Vector4(1.0f, 1.0f, 0.0f, 1.0f); // AMARILLO: ángulo = 90°
        }

        auto targetItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.4f)), new physx::PxTransform(targets[i]), color);
        renderItems.push_back(targetItem);
    }

    // ---------------------------------------------------------------------
    // ACTIVIDAD 4 - RETO C: Interpolación Lineal (Lerp)
    // ---------------------------------------------------------------------
    Vector3D A(-8.0f, 1.0f, -8.0f);
    Vector3D B(8.0f, 8.0f, 8.0f);

    int numPuntos = 10;
    for (int i = 0; i <= numPuntos; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(numPuntos);
        Vector3D Pt = A + (B - A) * t;

        auto lerpItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.2f)), new physx::PxTransform(Pt), Vector4(0.8f, 0.8f, 0.8f, 1.0f));
        renderItems.push_back(lerpItem);
    }
}

// -------------------------------------------------------------------------
// ACTIVIDAD 3: Limpieza de memoria (cleanup)
// -------------------------------------------------------------------------
void P0S_Scene::cleanup() {
    for (auto item : renderItems) {
        if (item != nullptr) {
            item->release(); // Liberación limpia usando release()
        }
    }
    renderItems.clear();
}