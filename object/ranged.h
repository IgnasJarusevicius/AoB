#ifndef RANGED_H
#define RANGED_H
#include "character.h"

//------------------------------------------------------------------------------

class Ranged : public Character {
public:
    Ranged(float xx, float yy, const UnitStats &stats);
    bool Attack(Character*);

    void Att_End() {
    };
};
//------------------------------------------------------------------------------

class Arrow : public Game_Object {
public:
    Arrow(float, float);

    ~Arrow() {
    };
    void Step();
    float xspeed, yspeed;
    Ranged* shooter;
    int delay;
    int dmg;

};
//------------------------------------------------------------------------------
#endif
