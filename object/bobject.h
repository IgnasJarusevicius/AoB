#ifndef BOBJECT_H
#define BOBJECT_H
#include "Picture.h"
#include "graphic/sprite.h"

//------------------------------------------------------------------------------
class Game_Object
{
public:
    Game_Object(float xx, float yy, float zz);
    virtual ~Game_Object();
    virtual void EndTurn(){};
    virtual void Step();
    virtual bool Collision(float,float,int);  
    Game_Object* next;
    int player;
    float x ,y, z;  
    float image_index;
protected:
    Sprite* sprite;
    Picture* image;
    float image_speed;
    float radius;  
};
//------------------------------------------------------------------------------
#endif
