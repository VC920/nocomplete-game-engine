#pragma once
#include "application.h"

class Game : public Application
{
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
};