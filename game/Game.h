#pragma once
#include "Engine.h"
#include <memory>

class Game : public eng::Application
{
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
private:
    std::unique_ptr<eng::Material> m_material;
    std::unique_ptr<eng::Mesh> m_mesh;
    float m_offsetX = 0.0f;
    float m_offsetY = 0.0f;
};