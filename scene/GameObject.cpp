#include "GameObject.h"

namespace eng
{
    void GameObject::Update(float deltaTime)
    {
        for (auto it = m_children.begin(); it != m_children.end();)
        {
            // 如果子对象激活更新
            if ((*it)->IsAlive())
            {
                (*it)->Update(deltaTime);
                ++it;
            }
            // 如果子对象禁用删除
            else
            {
                it = m_children.erase(it);
            }
        }
    }

    const std::string& GameObject::GetName() const
    {
        return m_name;
    }

    void GameObject::SetName(const std::string& name)
    {
        m_name = name;
    }

    GameObject* GameObject::GetParent()
    {
        return m_parent;
    }

    bool GameObject::IsAlive() const
    {
        return m_isAlive;
    }

    void GameObject::MarkForDestroy()
    {
        m_isAlive = false;
    }
}