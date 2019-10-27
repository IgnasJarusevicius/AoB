#include "object.h"

Orc::Orc(int p): Character(StatsOrc, p)
{
}

Pirate::Pirate(int p): Character(StatsPirate, p)
{
}

Barbarian::Barbarian(int p): Character(StatsBarbarian, p)
{
}

SkelWar::SkelWar(int p): Character(StatsSkelWar, p)
{
}

Viking::Viking(int p): Character(StatsViking, p)
{
}

Lava::Lava(int p): Character(StatsLava, p)
{
}

Knight::Knight(int p): Character(StatsKnight, p)
{
}

Dwarf::Dwarf(int p): Character(StatsDwarf, p)
{
}

Hunter::Hunter(int p): Ranged(StatsHunter, p)
{
}

SkelArch::SkelArch(int p): Ranged(StatsSkelArch, p)
{
    att_types.push_back(new PreciseShot(stats));
}

Archer::Archer(int p): Ranged(StatsArcher, p)
{
    att_types.push_back(new PreciseShot(stats));
    att_types.push_back(new CripplingShot(stats));
}

//------------------------------------------------------------------------------


Obstacle::Obstacle(int grid_x, int grid_y, Grid* grid, unsigned tex, int x0, int y0, int size) :
    GridObject(grid_x, grid_y, grid, size),
    image(x-x0, y-y0, -y, tex)
{
}

bool Obstacle::IsDestructable() const
{
    return false;
}

void Obstacle::Enable(bool en)
{
    image.Enable(en);
}

Tree::Tree(int grid_x, int grid_y, Grid* grid) :
    Obstacle(grid_x, grid_y, grid,Graphic_Resources::textures[TREE1], 64, 32, 1)
{
}

float Tree::GetSize() const
{
    return 20.0f;
}


//------------------------------------------------------------------------------
Rock::Rock(int grid_x, int grid_y, Grid* grid) :
    Obstacle(grid_x, grid_y, grid,Graphic_Resources::textures[ROCK1], 33, 28, 1)
{
}
//------------------------------------------------------------------------------
float Rock::GetSize() const
{
    return 40.0f;
}

Rock2::Rock2(int grid_x, int grid_y, Grid* grid) :
    Obstacle(grid_x, grid_y, grid,Graphic_Resources::textures[ROCK2], 48, 40, 2)
{
}
//------------------------------------------------------------------------------
float Rock2::GetSize() const
{
    return 80.0f;
}