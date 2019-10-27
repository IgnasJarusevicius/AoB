#include "object.h"
#include "graphic/gres.h"
//------------------------------------------------------------------------------

const UnitStats SkelArch =    { 40, 13,  6,  0, 85, 5,  6, PLAY_BOW, PLAY_STEP, PLAY_DIE2, 16.0f, Graphic_Resources::skelarc_sprites};
const UnitStats Hunter =      { 40,  7,  7,  0,  0, 6,  7, PLAY_BOW, PLAY_STEP2, PLAY_DIE, 16.0f, Graphic_Resources::hunter_sprites};
const UnitStats Orc =         { 60,  8,  4, 10,  0, 7, 10, PLAY_ATT, PLAY_STEP2, PLAY_DIE, 16.0f, Graphic_Resources::orc_sprites};
const UnitStats SkelWar =     { 50, 16,  4, 20, 85, 6,  8, PLAY_SWORD, PLAY_STEP2, PLAY_DIE2, 16.0f, Graphic_Resources::skelarc_sprites};
const UnitStats Pirate =      { 50, 11,  2,  0,  0, 8, 12, PLAY_ATT, PLAY_STEP4, PLAY_DIE, 16.0f, Graphic_Resources::pirate_sprites};
const UnitStats Barbarian =   { 80, 17,  8,  0,  0, 8, 11, PLAY_AXE, PLAY_STEP4, PLAY_DIE, 16.0f, Graphic_Resources::barbar_sprites};
const UnitStats Viking =      {100, 23,  6, 50, 25, 7,  9, PLAY_SWORD, PLAY_STEP3, PLAY_DIE, 16.0f, Graphic_Resources::viking_sprites};
const UnitStats Lava =        {150, 20, 10, 10, 40, 6,  8, PLAY_WHIP, PLAY_STEP2, PLAY_DIE2, 16.0f, Graphic_Resources::lava_sprites};
const UnitStats Archer =      { 70, 25,  5, 10, 20, 6,  8, PLAY_BOW, PLAY_STEP2, PLAY_DIE, 16.0f, Graphic_Resources::archer_sprites};
const UnitStats Knight =      { 90, 24,  3, 70, 70, 6,  8, PLAY_SWORD, PLAY_STEP2, PLAY_DIE, 16.0f, Graphic_Resources::knight_sprites};
const UnitStats Dwarf =       {120, 28, 14, 30, 60, 7, 10, PLAY_AXE, PLAY_STEP3, PLAY_DIE, 16.0f, Graphic_Resources::dwarf_sprites};

const UnitStats unit_data[UNIT_CNT] =
{
    Orc,
    Pirate,
    Hunter,
    Barbarian,
    SkelWar,
    SkelArch,
    Viking,
    Lava,
    Archer,
    Knight,
    Dwarf
};

//------------------------------------------------------------------------------
Tree::Tree(float set_x, float set_y) : Game_Object(set_x, set_y, 16.0f - set_y)
{
    radius = 12.0f;
    player = 0;
    sprite = Graphic_Resources::sprites[TREE1];
    image = new Picture(x, y, -y, sprite->images[0]);
}

//------------------------------------------------------------------------------
Rock::Rock(float set_x, float set_y) : Game_Object(set_x, set_y, -set_y)
{
    radius = 24;
    player = 0;
    sprite = Graphic_Resources::sprites[ROCK1];
    image = new Picture(x, y, -y, sprite->images[0]);
}
//------------------------------------------------------------------------------


