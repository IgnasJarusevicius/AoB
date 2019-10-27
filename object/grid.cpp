#include "grid.h"
#include "graphic/gres.h"
#include "object.h"
#include "TextObj.h"

constexpr float backTexSize = 128.0f;

Grid::Grid(float xx, float yy) :
    x(xx),
    y(yy),
    background(xx, yy, -1000.0f, Tile(Graphic_Resources::textures[GRASS], 0.0f, Grid::width/backTexSize, 0.0f, Grid::height/backTexSize))
{
}

Grid::~Grid()
{
    for (auto& obj : unit)
        if (obj)
            delete obj;
}

std::pair<int, int> Grid::GridPos(std::complex<float> pos) const
{
    return {int(pos.real()-x)/slotSize, int(pos.imag()-y)/slotSize};
}

std::complex<float> Grid::WorldPos(std::pair<int, int> pos) const
{
    return {x+(0.5f+pos.first)*slotSize, y+(0.5f+pos.second)*slotSize};
}


const std::vector<Grid::GridObject*>& Grid::GetUnits() const
{
    return unit;
}

void Grid::Enable(bool en)
{
    background.Enable(en);
}

Grid::GridObject::GridObject(int grid_x, int grid_y, Grid* g, int size) :
    grid_size(size)
{
    AddToGrid(grid_x, grid_y, g);
}

Grid::GridObject::GridObject(int size) :
    grid_size(size)
{
}

void Grid::GridObject::AddToGrid(int grid_x, int grid_y, Grid* g)
{
    grid = g,
    x = (grid->x+(grid_x+grid_size/2.0f)*Grid::slotSize);
    y =(grid->y+(grid_y+grid_size/2.0f)*Grid::slotSize);
    g->unit.push_back(this);
}

std::complex<float> Grid::GridObject::GetWorldPos() const
{
    return {x,y};
}

Grid::GridObject::GridSize Grid::GridObject::GetGridPos() const
{
    GridSize ret;
    float offset = (grid_size-1)*Grid::slotSize/2.0f;
    auto pos = grid->GridPos({x-offset,y-offset});
    for (int i = 0; i < grid_size; i++)
        for (int j = 0; j < grid_size; j++)
            ret.push_back({i+pos.first, j+pos.second});
    return ret;
}


