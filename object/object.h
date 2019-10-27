#ifndef OBJECT_H
#define OBJECT_H
#include "ranged.h"
#include "graphic/gres.h"
#include "data_types.h"

//hp , dmg1, dmg2, def1, def2, speed, ap
constexpr UnitResources StatsSkelArch = {
    {40, 8, 8, 13, 6, DamageType::RANGED, 0, 85},  //stats
    160,                                        //speed
    PLAY_BOW, PLAY_STEP, PLAY_DIE2,             //sounds
    Graphic_Resources::skelarc_sprites          //images
};

constexpr UnitResources StatsHunter = {
    {40, 9, 9, 7, 7, DamageType::RANGED, 0, 0},
    180,
    PLAY_BOW, PLAY_STEP2, PLAY_DIE,
    Graphic_Resources::hunter_sprites
};

constexpr UnitResources StatsOrc = {
    {60, 11, 11, 8, 4, DamageType::MELEE, 10, 0},
    220,
    PLAY_ATT, PLAY_STEP2, PLAY_DIE,
    Graphic_Resources::orc_sprites
};

constexpr UnitResources StatsSkelWar = {
    {50, 9, 9, 16, 4, DamageType::MELEE, 20, 85},
    180,
    PLAY_SWORD, PLAY_STEP2, PLAY_DIE2,
    Graphic_Resources::skelwar_sprites
};

constexpr UnitResources StatsPirate = {
    {50, 12, 12, 11, 2, DamageType::MELEE, 0, 0},
    240,
    PLAY_ATT, PLAY_STEP4, PLAY_DIE,
    Graphic_Resources::pirate_sprites
};

constexpr UnitResources StatsBarbarian = {
    {80, 12, 12, 17, 8, DamageType::MELEE, 0, 0},
    240,
    PLAY_AXE, PLAY_STEP4, PLAY_DIE,
    Graphic_Resources::barbar_sprites
};

constexpr UnitResources StatsViking = {
    {100, 10, 10, 23, 6, DamageType::MELEE, 50, 25},
    200,
    PLAY_SWORD, PLAY_STEP3, PLAY_DIE,
    Graphic_Resources::viking_sprites
};

constexpr UnitResources StatsLava = {
    {150, 9, 9, 20, 10, DamageType::MELEE, 10, 40},
    180,
    PLAY_WHIP, PLAY_STEP2, PLAY_DIE2,
    Graphic_Resources::lava_sprites
};

constexpr UnitResources StatsArcher = {
    {70, 9, 9, 25, 5, DamageType::RANGED, 10, 20},
    180,
    PLAY_BOW, PLAY_STEP2, PLAY_DIE,
    Graphic_Resources::archer_sprites
};

constexpr UnitResources StatsKnight = {
    {90, 9, 9, 24, 3, DamageType::MELEE, 70, 70},
    180,
    PLAY_SWORD, PLAY_STEP2, PLAY_DIE,
    Graphic_Resources::knight_sprites
};

constexpr UnitResources StatsDwarf = {
    {120, 11, 11, 28, 14, DamageType::MELEE, 30, 60},
    220,
    PLAY_AXE, PLAY_STEP3, PLAY_DIE,
    Graphic_Resources::dwarf_sprites
};

class Orc : public Character
{
public:
    Orc(int p);
};

class Pirate : public Character
{
public:
    Pirate(int p);
};

class Barbarian : public Character
{
public:
    Barbarian(int p);
};

class SkelWar : public Character
{
public:
    SkelWar(int p);
};

class Viking : public Character
{
public:
    Viking(int p);
};

class Lava : public Character
{
public:
    Lava(int p);
};

class Knight : public Character
{
public:
    Knight(int p);
};

class Dwarf : public Character
{
public:
    Dwarf(int p);
};

class Hunter : public Ranged
{
public:
    Hunter(int p);
};

class SkelArch : public Ranged
{
public:
    SkelArch(int p);
};

class Archer : public Ranged
{
public:
    Archer(int p);
};

    
//------------------------------------------------------------------------------  
class Obstacle : public Grid::GridObject
{
public:
    Obstacle(int grid_x, int grid_y, Grid* grid, unsigned tex, int x0, int y0, int size = 1);
    bool IsDestructable() const override;
    void Enable(bool en = true);
private:
    Picture image;   
};

class Tree : public Obstacle {
public:
    Tree(int grid_x, int grid_y, Grid* grid);
    float GetSize() const override;
};

//------------------------------------------------------------------------------    

class Rock : public Obstacle {
public:
    Rock(int grid_x, int grid_y, Grid* grid);
    float GetSize() const override;
};

class Rock2 : public Obstacle {
public:
    Rock2(int grid_x, int grid_y, Grid* grid);
    float GetSize() const override;
};
//------------------------------------------------------------------------------          
#endif



