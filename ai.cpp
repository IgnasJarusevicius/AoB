#include "ai.h"
#include <cstdlib>
#include <cmath>
#include "Battle.h"
#define PREC 5  //collision line precision lower = better

void AI::AI_Init()
{
    enemy_list.clear();
    for (Game_Object* current = Battle::first; current != NULL; current = current->next)
        if (current->player == 2)
            enemy_list.push_front((Character*)current);
}

//------------------------------------------------------------------------------

void AI::Get_Targets()
{
    Game_Object* current;
    Character* ccurrent, *archer;
    float temp;
    float dist(4000.0f);
    archer = NULL;
    lowhp = NULL;
    lowdef = NULL;
    kill = NULL;
    maxdmg = NULL;
    targets.clear();

    for (current = Battle::first; current != NULL; current = current->next)
        if (current->player == 1)
        {
            ccurrent = (Character*)current;
            targets.push_front(ccurrent);
            temp = floor(std::sqrt((selected->x - current->x)*(selected->x - current->x)+(selected->y - current->y)*(selected->y - current->y)));
            if (temp < dist)
            {
                dist = temp;
                nearest = ccurrent;
            }
            if (!selected->ranged)
                if (temp > (selected->movement + 2) * SLOT / 2)
                    continue;

            int armor = selected->ranged ? ccurrent->def2 : ccurrent->def;

            if (ccurrent->hp <= (selected->dmg + selected->dmg2 / 3 - (selected->dmg * armor) / 100))
                if ((!kill) || ((kill)&&(ccurrent->hp > kill->hp)))
                    kill = ccurrent;

            if (!lowhp)
                lowhp = lowdef = maxdmg = ccurrent;

            if (ccurrent->hp < lowhp->hp)
                lowhp = ccurrent;

            if (selected->ranged)
            {
                if (ccurrent->def2 < lowdef->def2)
                    lowdef = ccurrent;
            }
            else
                if (ccurrent->def < lowdef->def)
                lowdef = ccurrent;

            if (ccurrent->dmg > maxdmg->dmg)
                maxdmg = ccurrent;

            if ((selected->ranged)&&(ccurrent->ranged)&&(ccurrent->def2 < 30))
                if ((!archer) || ((archer)&&(archer->hp > ccurrent->hp)))
                    archer = ccurrent;
        }
    if ((!kill)&&(archer))
        kill = archer;
}

//------------------------------------------------------------------------------

bool AI::Collision_Line(Game_Object* obj, Game_Object* obj2, float x1 = -1.0f, float y1 = -1.0f)
{
    Game_Object* coll;

    float xx = x1 < 0.0f ? obj->x : x1;
    float yy = y1 < 0.0f ? obj->y : y1;
    float dx = obj2->x - xx;
    float dy = obj2->y - yy;
    float k = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    dx = PREC * dx / k;
    dy = PREC * dy / k;

    while (1)
    {
        xx += dx;
        yy += dy;
        if ((coll = Battle::grid[(int)(xx - GRID_X) / SLOT][(int)(yy - GRID_Y) / SLOT]) != NULL)
            if (coll != obj)
            {
                if (coll == obj2)
                    return false;
                else if (coll->Collision(xx, yy, 0))
                    return true;
            }
    }
}

//------------------------------------------------------------------------------

bool AI::Attempt_Melee_Attack(Character* obj)
{
    if (selected->Attack(obj))
    {
        enemy_list.remove(selected);
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------

bool AI::Melee_Action()
{
    if (selected->att)
    {
        if ((kill)&&(selected->Attack(kill)))
        {
            return false;
        }

        if (lowdef)
        {
            if (lowhp->def <= lowdef->def + 20)
                if (Attempt_Melee_Attack(lowhp))
                    return false;

            if (maxdmg->def <= lowdef->def + 20)
                if (Attempt_Melee_Attack(maxdmg))
                    return false;

            if (Attempt_Melee_Attack(lowhp))
                return false;

            if (Attempt_Melee_Attack(lowdef))
                return false;
        }
        for (auto& obj : targets )
            if (Attempt_Melee_Attack(obj))
                return false;
    }

    if (selected->movement < 2)
    {
        enemy_list.remove(selected);
        return false;
    }

    float temp;
    int a(-1), b;
    float x1, y1;
    float dist = floor(sqrt((selected->x - nearest->x)*(selected->x - nearest->x)+(selected->y - nearest->y)*(selected->y - nearest->y)));

    for (int i = 0; i < H_SLOT_NUMBER; i++)
        for (int j = 0; j < V_SLOT_NUMBER; j++)
            if ((Battle::action_zone[i][j] != 0)&&(Battle::action_zone[i][j] != selected->movement + 1))
            {
                x1 = GRID_X + i * SLOT + SLOT / 2 - nearest->x;
                y1 = GRID_Y + j * SLOT + SLOT / 2 - nearest->y;
                temp = floor(sqrt(x1 * x1 + y1 * y1));
                if (temp <= dist)
                {
                    if ((std::fabs(temp - dist) < 8.0f)&&(std::rand() % 3))
                        continue;
                    a = i;
                    b = j;
                    dist = temp;
                }
            }
    if (a != -1)
    {
        selected->Move(a, b);
        Battle::grid[a][b] = selected;
    }

    enemy_list.remove(selected);
    return false;
}

//------------------------------------------------------------------------------

bool AI::Ranged_Action()
{
    if (kill)
        if (Attempt_Ranged_Attack(kill))
            return false;

    if (lowdef)
    {
        if (lowhp->def2 <= lowdef->def2 + 20)
            if (Attempt_Ranged_Attack(lowhp))
                return false;

        if (maxdmg->def2 <= lowdef->def2 + 20)
            if (Attempt_Ranged_Attack(maxdmg))
                return false;

        if (Attempt_Ranged_Attack(lowdef))
            return false;

        if (Attempt_Ranged_Attack(maxdmg))
            return false;
    }

    for (auto& obj : targets)
        if (Attempt_Ranged_Attack(obj))
            return false;

    enemy_list.remove(selected);
    return false;
}

//------------------------------------------------------------------------------

bool AI::Attempt_Ranged_Attack(Character* obj)
{
    if (!Collision_Line(selected, obj))
    {
        selected->Attack(obj);
        enemy_list.remove(selected);
        return true;
    }
    else
        for (int i = H_SLOT_NUMBER - 1; i >= 0; i--)
            for (int j = V_SLOT_NUMBER - 1; j >= 0; j--)
                if (Battle::action_zone[i][j] != 0)
                    if (!Collision_Line(selected, obj, GRID_X + i * SLOT + SLOT / 2, GRID_Y + j * SLOT + SLOT / 2))
                    {
                        selected->Move(i, j);
                        Battle::grid[i][j] = selected;
                        return true;
                    }

    return false;
}

//------------------------------------------------------------------------------

bool AI::AI_Act()
{
    if (enemy_list.empty())
        return true;
    selected = enemy_list.front();
    Battle::Select(selected);
    Get_Targets();
    if (targets.empty())
        return true;

    if (selected->ranged)
        return Ranged_Action();
    else
        return Melee_Action();
}
//------------------------------------------------------------------------------







