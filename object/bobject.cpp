#include "bobject.h"

//------------------------------------------------------------------------------
Game_Object::Game_Object(float xx, float yy, float zz): x(xx),y(yy),z(zz)
{
    image_speed = 0.0f;
    image_index = 0.0f;
    image = nullptr;
}

Game_Object::~Game_Object()
{
    if (image)
        delete image;
    image = nullptr;
}

void Game_Object::Step()
{
    image->SetColor(player == 2 ? glm::vec3(0.6f,0.6f,0.6f) : glm::vec3(1.0f,1.0f,1.0f));
    image->SetPosition(x+(sprite->x1+sprite->x2)/2,y+(sprite->y1+sprite->y2)/2, -y);
    image->SetTexture(sprite->images[(int)floor(image_index)]);
 }

//------------------------------------------------------------------------------
bool Game_Object::Collision(float xx,float yy, int dmg)
{
    if ( std::sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y))<radius)
        return true;
    else
        return false;
 }
//------------------------------------------------------------------------------
