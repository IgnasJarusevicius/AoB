#include "GameObject.h"

ObjectGroup::~ObjectGroup()
{
    for (auto& obj : objects)
        delete obj;
}

int ObjectGroup::Step(float deltaTime)
{
    for (auto& obj : objects)
        obj->Step(deltaTime);
    return 0;
}

void ObjectGroup::Add(GameObject* obj)
{
    objects.push_back(obj);
}

void ObjectGroup::Enable(bool en)
{
    for (auto& obj : objects)
        obj->Enable(en);
}









