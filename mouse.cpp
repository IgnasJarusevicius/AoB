#include "mouse.h"

float Mouse::x;
float Mouse::y;
int Mouse::buttons;

bool Mouse::Position(float x1, float x2, float y1, float y2)
{
    if ((x >= x1)
        &&(x <= x2)
        &&(y >= y1)
        &&(y <= y2))
        return true;
    else
        return false;
}

bool Mouse::Button(int action)
{
    return ((action & buttons) == 0) ? false : true;
}

void Mouse::SetBut(int button)
{
    buttons |= button;
}

void Mouse::SetPos(float setx, float sety)
{
    x = setx;
    y = sety;
}

void Mouse::Reset()
{
    buttons = 0;
}
