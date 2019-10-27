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

struct UnitStats;

class Character: public Game_Object
{
public: 
    Character(float xx, float yy, const UnitStats &stats);
    virtual ~Character();
    Sprite* (*spriteset)[8]; 
    bool att;
    bool ranged;
    int movement;
    int hp;
    int maxhp;
    int dmg;
    int dmg2;
    int def;
    int def2;
    void EndTurn();
    void Move(int,int);
    void Step() override;
    void Animation_End();
    void Damage(int);
    bool Collision(float,float,int);        
    virtual bool Attack(Character*);
protected:
    int direction;
    int sounds[3];
    Character* target;
    Path path;
    int maxmove;
    int speed;
    int state;
private:    
    float Speed_x(int);
    float Speed_y(int);
    virtual void Att_End();             
}; 
//------------------------------------------------------------------------------
#endif
