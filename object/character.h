#ifndef CHARACTER_H
#define CHARACTER_H
#include "bobject.h"
#include "list.h"
#include "audio.h"
//------------------------------------------------------------------------------
#define SLOT 48
#define H_SLOT_NUMBER 15
#define V_SLOT_NUMBER 14
#define GRID_X 264
#define GRID_Y 40
//------------------------------------------------------------------------------
class Character: public Game_Object
{
      public: virtual ~Character();
              int direction;
              SpriteSet* spriteset; 
              bool att;
              bool ranged;
              int speed;
              int state;
              Path* path;
              int movement;
              int maxmove;
              int hp;
              int maxhp;
              int dmg;
              int dmg2;
              int def;
              int def2;
              int sounds[3];
              Character* target;
              void EndTurn();
              void Move(int,int);
              void Step();
              void Animation_End();
              void Damage(int);
              bool Collision(float,float,int);        
              virtual bool Attack(Character*);
     private: 
              float Speed_x(int);
              float Speed_y(int);
              virtual void Att_End();             
      } ; 
//------------------------------------------------------------------------------
#endif
