#pragma once
#include <vector>
#include <forward_list>
//------------------------------------------------------------------------------

class GameObject
{
public:
    static void UpdateAll(float dt);
    static void Clear();
    virtual ~GameObject();
    virtual void Step(float deltaTime = 0.0f){};
    virtual void Enable(bool en = true){};
protected:
    GameObject(); 
private:
    static std::forward_list<GameObject*> objList;
};







