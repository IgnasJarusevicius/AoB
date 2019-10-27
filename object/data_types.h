#pragma once
#include "graphic/gres.h"
enum DamageType 
{
    MELEE = 0,
    RANGED,
    ATT_TYPE_CNT
};

struct UnitStats
{
    int hp;
    float ap;
    float ap_regen;
    float dmg_base;
    float dmg_rand;
    DamageType dmg_type;
    float defense[ATT_TYPE_CNT];
};

struct UnitInfo
{
    const UnitStats &stats;
    const UnitStats &base_stats;
    int player;
    Tile image;
};

struct UnitResources
{
    UnitStats stats;
    unsigned speed;
    int sound_att;
    int sound_step;
    int sound_die;
    Sprite* (*spriteset)[8];
};



