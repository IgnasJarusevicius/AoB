#ifndef SPRITE_H
#define SPRITE_H
#include <glad/glad.h>
#include <graphic/gres.h>
#include <vector>
//------------------------------------------------------------------------------
class Sprite
{
 public: 
    float x0, y0;
    std::vector<Tile> images;
    Sprite(std::vector<Tile> &&tiles, int xoff, int yoff);
};     
#endif 
