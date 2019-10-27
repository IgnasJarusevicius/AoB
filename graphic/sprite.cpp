#include "texture.h"
#include <GL/gl.h>
#include <cstdio>
#include <vector>
#include "sprite.h"

//------------------------------------------------------------------------------
typedef unsigned char Byte;


Sprite::Sprite(std::vector<Tile> &&tiles, int xoff, int yoff) :
    x0(xoff),
    y0(yoff)
{
    std::swap(tiles, images);
}
//-----------------------------------------------------------------------------


