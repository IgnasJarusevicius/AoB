#include "bobject.h"
#include "grid.h"


Unit::Unit(int p):
    player(p)
{
    image_speed = 0.0f;
    image_index = 0.0f;
    image = nullptr;
}

Unit::~Unit()
{
    if (image)
        delete image;
    image = nullptr;
}

bool Unit::IsDestructable() const
{
    return true;
}

void Unit::Enable(bool en)
{
    image->Enable(en);
}


