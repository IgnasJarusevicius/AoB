#pragma once
#include <vector>
//------------------------------------------------------------------------------

class GameObject
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;
    virtual int Step(float deltaTime = 0.0f)=0;
    virtual void Enable(bool en = true) = 0;
};

class ObjectGroup : public GameObject
{
public:
    ObjectGroup() = default;
    ~ObjectGroup();
    int Step(float deltaTime = 0.0f) override;
    void Add(GameObject* obj);
    void Enable(bool en = true);
private:
    std::vector<GameObject*> objects;    
};





