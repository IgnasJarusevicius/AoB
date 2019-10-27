#include "texture.h"
#include <GL/gl.h>
#include <cstdio>
#include "sprite.h"

//------------------------------------------------------------------------------
typedef unsigned char Byte;

//------------------------------------------------------------------------------

Sprite::Sprite(const char* name, int cnt, int xof, int yof)
{
    char ch[256];
    int width, height;
    images = new GLuint[cnt];
    for (int i(0); i < cnt; i++)
    {
        std::snprintf(ch, sizeof(ch), "%s%02d.bmp", name, i);
        images[i] = Texture(ch, true);
    }
    image_number = cnt;

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

    if (xof == -1)
    {
        x2 = width / 2;
        x1 = -x2;
        y2 = 3 * height / 4;
        y1 = y2 - height;
    }
    else
    {
        x1 = -xof;
        x2 = width - xof;
        y1 = -yof;
        y2 = height - yof;
    }
}
//------------------------------------------------------------------------------

Sprite::Sprite(const Sprite* spr, int ind)
{
    images = &(spr->images[ind]);
    image_number = 1.0f;
    x1 = spr->x1;
    x2 = spr->x2;
    y1 = spr->y1;
    y2 = spr->y2;
}
//------------------------------------------------------------------------------

Sprite::~Sprite()
{
    for (int i(0); i < image_number; i++)
        glDeleteTextures(1, &(images[i]));
}
//------------------------------------------------------------------------------

