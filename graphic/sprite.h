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
         Sprite(Sprite* spr, int ind); 
         ~Sprite();
 private:
         GLuint LoadTexture(const char * filename);  
         
 };
//------------------------------------------------------------------------------ 
class SpriteSet
{
 public: ~SpriteSet();
         Sprite* sprites[4][8];
 
      };  
//------------------------------------------------------------------------------            
#endif 
