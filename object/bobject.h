#ifndef BOBJECT_H
#define BOBJECT_H
#include "graphic/graphics.h"
//------------------------------------------------------------------------------
class Game_Object
{
      public:
              float x ,y, z;  
              Sprite* sprite;
              float image_index;
              float image_speed;
              float radius;
              Game_Object* next;
              int player;           
              virtual void EndTurn(){};
              virtual void Draw();
              virtual void Step(){};
              virtual bool Collision(float,float,int);         
      };
//------------------------------------------------------------------------------
#endif
