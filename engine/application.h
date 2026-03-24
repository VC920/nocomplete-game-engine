#pragma once

class Application
{
public:
    virtual bool Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Destroy() = 0;

    void SetShouldClosed(bool value);
    bool ShouldClosed() const;

private:
    bool m_shouldClosed = false;
};
