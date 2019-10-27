#include "GameObject.h"

std::forward_list<GameObject*> GameObject::objList;

GameObject::GameObject()
{
    objList.push_front(this);
}

GameObject::~GameObject()
{
    objList.remove(this);
}

void GameObject::UpdateAll(float dt)
{
    auto it = objList.begin();
    while (it != objList.end())
    {
        auto tmp = *it++;       //allow removing items while iterating
        tmp->Step(dt);
    }
}

void GameObject::Clear()
{
    auto it = objList.begin();
    while (it != objList.end())
    {
        auto tmp = *it++;
        delete tmp;
    }
}









