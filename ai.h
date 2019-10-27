#ifndef AI_H
#define AI_H
#include "object/object.h"
#include <forward_list>

class AI {
public:
    AI() = default;
    ~AI() = default;
    void AI_Init();
    bool AI_Act();
private:
    bool Collision_Line(Game_Object*, Game_Object*, float, float);
    void Get_Targets();
    bool Melee_Action();
    bool Ranged_Action();
    bool Attempt_Ranged_Attack(Character*);
    bool Attempt_Melee_Attack(Character*);
    std::forward_list<Character*> enemy_list;
    std::forward_list<Character*> targets;
    Character* selected;
    Character* nearest;
    Character* lowhp;
    Character* lowdef;
    Character* kill;
    Character* maxdmg;
};
#endif
