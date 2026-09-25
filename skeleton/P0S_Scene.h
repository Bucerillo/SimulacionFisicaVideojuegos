#pragma once
#include "Scene.h"
#include <vector>

class RenderItem;

class P0S_Scene : public Scene {
public:
    P0S_Scene() = default;
    ~P0S_Scene() override = default;

    // Función estática creadora
    static Scene* create() { return new P0S_Scene(); }

    void init() override;
    void update(double dt) override {}
    void cleanup() override;
    void keyPress(unsigned char key, const physx::PxTransform& cameraTransform) override {}

private:
    std::vector<RenderItem*> renderItems;
};