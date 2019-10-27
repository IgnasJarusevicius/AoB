#ifndef DAMAGE_H
#define DAMAGE_H
#include "bobject.h"
#include "TextObj.h"

class Damage_Report: public Game_Object
{
public:
      Damage_Report(float,float); 
      void SetValue(std::string val);
private:
      int life;
      void Step();    
      TextObj text;
}; 

#endif
