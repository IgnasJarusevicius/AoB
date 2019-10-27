#include "ranged.h"
#include <cstdlib>
#include <cmath>
#include "audio.h"
#include "graphic/gres.h"
#include <iostream>

Ranged::Ranged(const UnitResources &s, int p) :
    Character(s, p),
    arrow(nullptr)
{
}
//------------------------------------------------------------------------------
void Ranged::ExecuteAttack()
{
    arrow = new Arrow(this);
}

bool Ranged::IsMoving() const
{
    if (arrow)
        return true;
    return Character::IsMoving();
}

Grid::GridData<int>* Ranged::Select()
{
    if (state != STAND)
        return nullptr;
    UpdateMoveRange();
    for (const auto& obj : grid->GetUnits())
    {
        if (obj && obj->IsDestructable() && obj != this)
        {
            const auto pos = obj->GetGridPos();
            if (pos.empty())
                continue;
            auto& mv = moveZone[pos[0].first][pos[0].second];
            if (CollisionLine(obj->GetWorldPos(), {x, y}) == 2)
            {
                mv = attack->GetAp();
            }
            else
            {
                for (unsigned i = 0; i< moveZone.width; i++)
                    for (unsigned j = 0; j< moveZone.height; j++)
                        if ((moveZone[i][j]+attack->GetAp() < mv) && (CollisionLine(grid->WorldPos({i, j}), obj->GetWorldPos()) == 1))
                            mv = moveZone[i][j]+attack->GetAp();
            }
        }
    }
    return &moveZone;
}

bool Ranged::Attack(Character* obj)
{
    int move_x;
    int move_y;

    if (CollisionLine({x, y}, obj->GetWorldPos()) == 2)
    {
        auto grid_pos = grid->GridPos({x, y});
        move_x = grid_pos.first;
        move_y = grid_pos.second;
    }
    else
    {
        auto pos = grid->GridPos(obj->GetWorldPos());
        move_x = pos.first;
        move_y = pos.second;
        for (unsigned i = 0; i< moveZone.width; i++)
            for (unsigned j = 0; j< moveZone.height; j++)
                if ((moveZone[i][j] < moveZone[move_x][move_y]) && (CollisionLine(grid->WorldPos({i, j}), obj->GetWorldPos()) == 1))
                {
                    move_x = i;
                    move_y = j;
                }
        if (move_x == pos.first && move_y == pos.second)
            return false;
    }

    if ((Move(move_x, move_y)==std::pair<int, int>({move_x, move_y})) && (stats.ap >= attack->GetAp()) && (obj->GetUnitInfo().player != player))
    {
        target = obj;
        return true;
    }
    return false;
}

int Ranged::CollisionLine(std::complex<float> pos1, std::complex<float> pos2) const
{
    const float x1 = pos1.real();
    const float y1 = pos1.imag();
    const float x2 = pos2.real();
    const float y2 = pos2.imag();
    const float k = (std::fabs(x1-x2) < 0.5) ? 0.0f : (y1-y2)/(x1-x2);
    const float h = y1-k*x1;
    const float mult = 1.0f/std::sqrt(k*k+1);
    int ret = 0;

    for (auto& obj : grid->GetUnits())
        if (obj)
        {
            auto pos = obj->GetWorldPos();
            if ((pos.real() > x1+0.5f) && (pos.real() > x2+0.5f))
                continue;
            if ((pos.real() < x1-0.5f) && (pos.real() < x2-0.5f))
                continue;
            if ((pos.imag() > y1+0.5f) && (pos.imag() > y2+0.5f))
                continue;
            if ((pos.imag() < y1-0.5f) && (pos.imag() < y2-0.5f))
                continue;
            if ((std::fabs(k)< 0.01f)||(std::fabs(pos.imag()-k*pos.real()-h)*mult < obj->GetSize()))
                ret++;
        }
    return ret;
}
//------------------------------------------------------------------------------

Ranged::Arrow::Arrow(Ranged* owner):
    shooter(owner),
    position(shooter->GetWorldPos()),
    image(shooter->x, shooter->y, -shooter->y, Graphic_Resources::arrow->images[0]),
    target(shooter->target),
    destination(target->GetWorldPos()),
    direction((destination-position)/std::fabs(destination-position))
{
    const float pi = std::acos(-1.0);
    const int img = (pi+arg(direction))*16.0f/pi+0.5f;
    image.SetTile(Graphic_Resources::arrow->images[img%32]);
}

//------------------------------------------------------------------------------

void Ranged::Arrow::Step(float dt)
{
    const float speed = 750.0f;
    if (std::fabs(position-destination) < speed*dt)
    {
        target->Damage(shooter->attack->GetDamage());
        shooter->arrow = nullptr;
        shooter->Select();
        delete this;
    }
    else
        position += speed*direction*dt;
    image.SetPosition(position.real()-16, position.imag()-20, 20-position.imag());
}


//------------------------------------------------------------------------------

