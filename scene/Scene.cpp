#include "Scene.h"

namespace eng
{
    void Scene::Update(float deltaTime)
    {
        for (auto it = m_objects.begin(); it != m_objects.end();)
        {
            // 如果对象激活更新
            if ((*it)->IsAlive())
            {
                (*it)->Update(deltaTime);
                ++it;
            }
            // 如果对象禁用删除
            else
            {
                it = m_objects.erase(it);
            }
        }
    }

    void Scene::Clear()
    {
        m_objects.clear();
    }

    GameObject* Scene::CreateObject(const std::string& name, GameObject* parent = nullptr)
    {
        auto obj = new GameObject();
        obj->SetName(name);
        SetParent(obj, parent);
        return obj;
    }

    bool Scene::SetParent(GameObject* obj, GameObject* parent)
    {
        return false;
    }
}