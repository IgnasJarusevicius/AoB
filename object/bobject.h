#ifndef BOBJECT_H
#define BOBJECT_H
#include "Picture.h"
#include "graphic/sprite.h"
#include "GameObject.h"
#include "grid.h"


class Unit : public GameObject, public Grid::GridObject
{
public:
    Unit(int p = 0);
    virtual ~Unit();
    bool IsDestructable() const override;
    virtual void Enable(bool en = false);
protected:
    float image_index;
    Sprite* sprite;
    Picture* image;
    float image_speed;
    int player;
};
//------------------------------------------------------------------------------
#endif
