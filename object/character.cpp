#include "character.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include "stats.h"
#include "object.h"
#include "damage.h"
#include <iostream>
#include <cstring>

Character::Character(const UnitResources& res, int p) :
    Unit(p),
    base_stats(res.stats),
    stats(base_stats),
    direction(p == 2 ? 4 : 0),
    sounds{res.sound_att, res.sound_step, res.sound_die},
    target(nullptr),
    speed(res.speed),
    state(STAND),
    spriteset(res.spriteset),
    hp_bar(0.0f, 0.0f, Grid::slotSize-6, 6),
    speed_x {1.0f*speed, 0.7071f*speed, 0.0f, -0.7071f*speed, -1.0f*speed, -0.7071f*speed, 0.0f, 0.7071f*speed},
    speed_y {0.0f, 0.7071f*speed, 1.0f*speed, 0.7071f*speed, 0.0f, -0.7071f * speed, -1.0f*speed, -0.7071f * speed},
    z(-y)
{
    image = new Picture(x, y, -y, spriteset[0][0]->images[0]);
    att_types.push_back(new NormalAttack(stats));
    attack = att_types[0];
}
//------------------------------------------------------------------------------

Character::~Character()
{
    for (auto& i : att_types)
        delete i;
}
//------------------------------------------------------------------------------

std::pair<int, int> Character::Move(int grid_x, int grid_y)
{
    auto grid_pos = grid->GridPos({x, y});
    if (state != STAND || moveZone[grid_x][grid_y] < 0)
        return grid_pos;
    path.clear();
    GetPath(grid_x, grid_y);
    if (path.size() < 2)
        return grid_pos;

    grid_pos = grid->GridPos(path[0]);

    stats.ap -= moveZone[grid_pos.first][grid_pos.second];

    x = path.back().real();
    y = path.back().imag();
    path.pop_back();

    SetDirection(path.back());
    image_speed = 15.0f;
    state = MOVE;
    Audio::Play(sounds[1]);
    return grid_pos;
}

void Character::UpdateMoveRange()
{
    for (auto& i : moveZone)
        i = 0x7FFF;
    for (const auto& unit : grid->GetUnits())
    {
        auto pos = unit->GetGridPos();
        for (auto& i : pos)
            moveZone[i.first][i.second] = -1;
    }

    auto pos = grid->GridPos({x, y});
    Check(pos.first, pos.second, 0);

    for (const auto& unit : grid->GetUnits())
    {
        auto pos = unit->GetGridPos();
        for (auto& i : pos)
            moveZone[i.first][i.second] = unit == this ? 0 : 0x7FFF;
    }
}

Grid::GridData<int>* Character::Select()
{
    UpdateMoveRange();

    for (const auto& obj : grid->GetUnits())
    {
        if (obj && obj->IsDestructable() && obj != this)
        {
            const auto pos = obj->GetGridPos();
            if (pos.empty())
                continue;
            int xx = pos[0].first;
            int yy = pos[0].second;
            for (int i = (xx > 0) ? xx-1 : 0; i < (xx<moveZone.width-1 ? xx+2 : moveZone.width); i++)
                for (int j = (yy > 0) ? yy-1 : 0; j < (yy<moveZone.height-1 ? yy+2 : moveZone.height); j++)
                    if ((moveZone[i][j]>=0) && (attack->GetAp()+moveZone[i][j] < moveZone[xx][yy]))
                        moveZone[xx][yy] = moveZone[i][j]+attack->GetAp();
        }
    }
    return &moveZone;;
}

bool Character::IsMoving() const
{
    return (state != STAND);
}

UnitInfo Character::GetUnitInfo() const
{
    return UnitInfo({stats, base_stats, player, spriteset[0][6]->images[0]});
}
//------------------------------------------------------------------------------

bool Character::Attack(Character* obj)
{
    auto pos = grid->GridPos(obj->GetWorldPos());
    const int xx = pos.first;
    const int yy = pos.second;
    int move_x = xx;
    int move_y = yy;
    for (int i = (xx > 0) ? xx-1 : 0; i < (xx<moveZone.width-1 ? xx+2 : moveZone.width); i++)
        for (int j = (yy > 0) ? yy-1 : 0; j < (yy<moveZone.height-1 ? yy+2 : moveZone.height); j++)
            if (moveZone[i][j] < moveZone[move_x][move_y])
            {
                move_x = i;
                move_y = j;
            }

    if (move_x == xx && move_y == yy)
        return false;

    if ((Move(move_x, move_y)==std::pair<int, int>({move_x, move_y})) && (stats.ap >= attack->GetAp()) && (obj->GetUnitInfo().player != player))
    {
        target = obj;
        return true;
    }
    return false;
}

void Character::SetDirection(std::complex<float> dest)
{
    direction = (arg(dest-std::complex<float>(x,y))*4.0f/3.14f);
    if (direction < 0)
        direction = 8 + direction;
}

//------------------------------------------------------------------------------
void Character::Animation_End()
{
    if (state == STAND)
        image_speed = 0.0f;

    if (state == ATTACK)
    {
        state = STAND;
        image_speed = 0.0f;
    }

    if (state == DIE)
    {
        state = DEAD;
        image_index = sprite->images.size()-1;
        stats.ap = 0;
        return;
    }
    image_index -= sprite->images.size();
}

void Character::ApplyEffects(float dt)
{
    if (dt != 0.0f)
    {
        for (auto it = effects.begin(); it!= effects.end();)
        {
            if ((*it)->UpdateLife(dt) == false)
            {
                delete *it;
                effects.erase(it);
                continue;
            }
            it++;
        }
    }
    stats.ap_regen = base_stats.ap_regen;
    stats.dmg_base = base_stats.dmg_base;
    stats.dmg_rand = base_stats.dmg_rand;
    std::memcpy(stats.defense, base_stats.defense, sizeof(stats.defense));
    for (auto i : effects)
        i->Apply(stats);
}

//------------------------------------------------------------------------------
void Character::ExecuteAttack()
{
   target->Damage(attack->GetDamage());
   Select();
}

int Character::Damage(AttackDamage&& dmg)
{
    int damage = dmg.base + dmg.rand * std::rand() / RAND_MAX;
    damage = damage - (damage * stats.defense[dmg.type]) / 100.0f;
    damage = damage > 1 ? damage : 1;

    if (damage >= stats.hp)
    {
        damage = stats.hp;
        state = DIE;
        Audio::Play(sounds[2]);
        image_speed = 16.0f;
        stats.ap = 0;
        stats.hp = 0;
        grid_size = 0;
    }
    else
        stats.hp -= damage;
    if ((dmg.effect) && (20+std::rand()%80 >= stats.defense[dmg.type]))
    {
        bool addeffect = true;
        for (auto eff : effects)
        {
            if (*eff == *dmg.effect)
            {
                eff->ResetLife();
                addeffect = false;
                break;
            }
        }
        new Effect_Report(x, y, dmg.effect->Name());
        if (addeffect)
        {
            effects.push_back(dmg.effect);
            dmg.effect = nullptr;
            ApplyEffects();
        }
    }
    new Damage_Report(x, y, std::to_string(-damage));
    return damage;
}
//------------------------------------------------------------------------------

void Character::EndTurn(float step, bool active)
{
    if (step < 0)
        return;

    if (stats.hp > 0)
    {
        if (active)
            stats.ap = stats.ap > 1.0f ? stats.ap-1.0f : 0.0f;
        ApplyEffects(step);
        float ap_gain = stats.ap_regen * step;
        if (ap_gain > base_stats.ap-stats.ap)
            ap_gain = base_stats.ap-stats.ap;
        stats.ap += ap_gain;
        if (ap_gain >= 1.0f)
            new AP_Report(x, y, std::string("+")+std::to_string(int(ap_gain))+" AP");
    }
}

float Character::GetSize() const
{
    return stats.hp > 0 ? 24.0f : 0.0f;
}

void Character::Enable(bool en)
{
    image->Enable(en);
    hp_bar.Enable(en);
}

const std::vector<AttackType*>& Character::GetAttackTypes() const
{
    return att_types;
}

void Character::SelectAttack(int index)
{
    attack = att_types[index];
    Select();
}
//------------------------------------------------------------------------------

void Character::Step(float dt)
{
    if (state == DEAD)
        return;
    sprite = spriteset[state][direction];
    image_index += image_speed*dt;
    if (image_index >= sprite->images.size())
        Animation_End();

    if (state == MOVE)
    {
        if (fabs(x - path.back().real()) + fabs(y - path.back().imag()) <= speed*dt)
        {
            x = path.back().real();
            y = path.back().imag();
            path.pop_back();
            if (!path.empty())
            {
                SetDirection(path.back());
            }
            else
            {
                image_speed = 0.0f;
                image_index = 0.0f;
                state = STAND;
                Audio::Stop(sounds[1]);
                Select();
            }
        }
        else
        {
            x += speed_x[direction]*dt;
            y += speed_y[direction]*dt;
        }
    }

    if ((state == ATTACK)&&(target)&&(image_index > 0.6f * sprite->images.size()))
    {
        Audio::Play(sounds[0]);
        ExecuteAttack();
        target = nullptr;
    }

    if (state == STAND)
    {
        if (rand() % 400 == 0)
            image_speed = 12.0f;
        if (target)
        {
            if (attack->GetAp() <= stats.ap)
            {
                state = ATTACK;
                image_index = 0;
                image_speed = 14.0f;
                SetDirection(target->GetWorldPos());
                stats.ap -= attack->GetAp();
            }
            else
                target = nullptr;
        }
    }
    if (stats.hp)
    {
        hp_bar.SetPosition(x-Grid::slotSize/2.2f, y-Grid::slotSize/2.25f);
        hp_bar.SetValue(float(stats.hp)/float(base_stats.hp));
    }
    else
    {
        hp_bar.Enable(false);
    }
    z = state == DEAD ? -y-100 : -y;
    image->SetPosition(x-sprite->x0, y-sprite->y0, z);
    image->SetTile(sprite->images[int(image_index)]);
}
//------------------------------------------------------------------------------

void Character::Check(int grid_x, int grid_y, int ind)
{
    moveZone[grid_x][grid_y] = ind;
    if((grid_y+1<moveZone.height)&&(moveZone[grid_x][grid_y+1] > ind+2))
        Check(grid_x, grid_y+1, ind+2);
    if((grid_y>0)&&(moveZone[grid_x][grid_y-1] > ind+2))
        Check(grid_x, grid_y-1, ind+2);
    if((grid_x+1<moveZone.width)&&(moveZone[grid_x+1][grid_y] > ind+2))
        Check(grid_x+1, grid_y, ind+2);
    if((grid_x>0)&&(moveZone[grid_x-1][grid_y] > ind+2))
        Check(grid_x-1, grid_y, ind+2);
    if((grid_x+1 < moveZone.width)&&(grid_y+1<moveZone.height)&&(moveZone[grid_x+1][grid_y+1] > ind+3))
        Check(grid_x+1, grid_y+1, ind+3);
    if((grid_x+1 < moveZone.width)&&(grid_y > 0)&&(moveZone[grid_x+1][grid_y-1] > ind+3))
        Check(grid_x+1, grid_y-1, ind+3);
    if((grid_x > 0)&&(grid_y+1<moveZone.height)&&(moveZone[grid_x-1][grid_y+1] > ind+3))
        Check(grid_x-1, grid_y+1, ind+3);
    if((grid_x > 0)&&(grid_y > 0)&&(moveZone[grid_x-1][grid_y-1] > ind+3))
        Check(grid_x-1, grid_y-1, ind+3);
}

void Character::GetPath(int grid_x, int grid_y)
{
    if (stats.ap >= moveZone[grid_x][grid_y])
        path.push_back(grid->WorldPos({grid_x, grid_y}));

    int val = moveZone[grid_x][grid_y];

    if((grid_y+1<moveZone.height)&&(moveZone[grid_x][grid_y+1]+2 == val))
        GetPath(grid_x, grid_y+1);
    else if((grid_y>0)&&(moveZone[grid_x][grid_y-1]+2 == val))
        GetPath(grid_x, grid_y-1);
    else if((grid_x+1<moveZone.width)&&(moveZone[grid_x+1][grid_y]+2 == val))
        GetPath(grid_x+1, grid_y);
    else if((grid_x>0)&&(moveZone[grid_x-1][grid_y]+2 == val))
        GetPath(grid_x-1, grid_y);
    else if((grid_x+1 < moveZone.width)&&(grid_y+1<moveZone.height)&&(moveZone[grid_x+1][grid_y+1]+3 == val))
        GetPath(grid_x+1, grid_y+1);
    else if((grid_x+1 < moveZone.width)&&(grid_y > 0)&&(moveZone[grid_x+1][grid_y-1]+3 == val))
        GetPath(grid_x+1, grid_y-1);
    else if((grid_x > 0)&&(grid_y+1<moveZone.height)&&(moveZone[grid_x-1][grid_y+1]+3 == val))
        GetPath(grid_x-1, grid_y+1);
    else if((grid_x > 0)&&(grid_y > 0)&&(moveZone[grid_x-1][grid_y-1]+3 == val))
        GetPath(grid_x-1, grid_y-1);
}
