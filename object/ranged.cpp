#include "ranged.h"
#include "Battle.h"
#include <cstdlib>
#include <cmath>
#include "audio.h"

Ranged::Ranged(float xx, float yy, const UnitStats &stats) : Character(xx, yy, stats)
{
    ranged = true;
}
//------------------------------------------------------------------------------

bool Ranged::Attack(Character* target)
{
    Arrow* obj;
    float dir;
    const float pi = std::acos(-1);
    Battle::active_control = false;
    state = 2;
    image_speed = 0.3f;
    image_index = 0.0f;
    obj = (Arrow*)Battle::Create(20, x, y);
    dir = atan2(target->y - y, target->x - x);
    obj->xspeed = 2.0f * std::cos(dir);
    obj->yspeed = 2.0f * std::sin(dir);
    obj->shooter = this;
    obj->delay = 16;
    obj->dmg = dmg + std::rand() % (dmg2 + 1);
    if (dir < -0.875f * pi)
        direction = 4;
    else if (dir < -0.625f * pi)
        direction = 5;
    else if (dir < -0.375f * pi)
        direction = 6;
    else if (dir < -0.125f * pi)
        direction = 7;
    else if (dir < 0.125f * pi)
        direction = 0;
    else if (dir < 0.375f * pi)
        direction = 1;
    else if (dir < 0.625f * pi)
        direction = 2;
    else if (dir < 0.875f * pi)
        direction = 3;
    else direction = 4;
    obj->image_index = 0;
    for (int i = 1; i < 32; i++)
        if (dir <= (i - 15) * pi / 16.0f - pi / 32.0f)
        {
            obj->image_index = i;
            break;
        }
    return 1;
}

//------------------------------------------------------------------------------

Arrow::Arrow(float set_x, float set_y) : Game_Object(set_x, set_y, -set_y)
{
    player = 0;
    sprite = Graphic_Resources::sprites[ARROW];
    image = new Picture(x, y, -y, sprite->images[0]);
}

//------------------------------------------------------------------------------

void Arrow::Step()
{
    Game_Object* obj;
    z = -y;
    if (delay != 0)
    {
        if (delay == 1)
        {
            Audio::Play(PLAY_BOW);
            shooter->att = false; //fixing bugs
        }
        delay--;
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        x += xspeed;
        y += yspeed;
        if ((obj = Battle::grid[(int)(x - GRID_X) / SLOT][(int)(y - GRID_Y) / SLOT]) != NULL)
            if (obj != shooter)
                if (obj->Collision(x, y, dmg))
                {
                    Audio::Play(PLAY_HIT);
                    Battle::active_control = true;
                    Battle::Remove(this);
                    return;
                }
    }
    Game_Object::Step();
}
//------------------------------------------------------------------------------

