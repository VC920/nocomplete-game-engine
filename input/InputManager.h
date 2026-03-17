#pragma once
#include <array>

namespace eng
{
    class InputManager
    {
    private:
        // 私有构造
        InputManager() = default;
        // 禁用拷贝移动 只允许Engine创建 
        InputManager(const InputManager&) = delete;
        InputManager(InputManager&&) = delete;
        InputManager& operator=(const InputManager&) = delete;
        InputManager& operator=(InputManager&&) = delete;
        
    public:
        void SetKeyPressed(int key, bool pressed);
        bool IsKeyPressed(int key);

    private:
        std::array<bool, 256> m_keys = {false};
        friend class Engine;
    };
}