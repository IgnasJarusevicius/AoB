#ifndef SPRITE_H
#define SPRITE_H
#include <GL/gl.h>
//------------------------------------------------------------------------------
class Sprite
{
 public: float x1,x2, y1, y2;
         GLuint* images;
         float image_number;
         Sprite(const char* name, int cnt, int xof = -1, int yof = 0);
         Sprite(const Sprite* spr, int ind); 
         ~Sprite();       
};     
#endif 
