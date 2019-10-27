#ifndef OBJECT_H
#define OBJECT_H
#include "ranged.h"
#include "damage.h"
#include "vector"

//------------------------------------------------------------------------------  

enum
{
    ORC = 0,
    PIRATE,
    HUNTER,
    BARBARIAN,
    SKELWAR,
    SKELARCH,
    VIKING,
    LAVA,
    ARCHER,    
    KNIGHT,
    DWARF,
    UNIT_CNT
};

struct UnitStats
{
    unsigned hp;
    unsigned dmg_base;
    unsigned dmg_var;
    unsigned def_melee;
    unsigned def_ranged;
    unsigned speed;
    unsigned movement;
    int sound_att;
    int sound_step;
    int sound_die;
    float radius;
    Sprite* (*spriteset)[8];
};

extern const UnitStats unit_data[UNIT_CNT];

//------------------------------------------------------------------------------          

class Tree : public Game_Object {
public:
    Tree(float, float);
};

//------------------------------------------------------------------------------    

class Rock : public Game_Object {
public:
    Rock(float, float);
};
//------------------------------------------------------------------------------          
#endif



