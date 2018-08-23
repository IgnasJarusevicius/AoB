#ifndef DAMAGE_H
#define DAMAGE_H
#include "bobject.h"

class Damage_Report: public Game_Object
{
      public:Damage_Report(float,float);
             ~Damage_Report();                           
             int life;
             const char* str;
             void Draw();
             void Step();           
      }; 

#endif
