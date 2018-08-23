#include "graphics.h"

//------------------------------------------------------------------------------
void Draw_Rectangle(float x1, float x2,float y1, float y2, float depth)
{
 glBegin(GL_QUADS);
      glVertex3f(x1,y1,depth);
      glVertex3f(x2,y1,depth);
      glVertex3f(x2,y2,depth);
      glVertex3f(x1,y2,depth);  
     glEnd();                  
 }
 
//------------------------------------------------------------------------------
 
void Draw_Rectangle_Outline(float x1, float x2,float y1, float y2, float depth)
{ 
 glBegin(GL_LINE_LOOP);
      glVertex3f(x1,y1,depth);
      glVertex3f(x1,y2,depth);
      glVertex3f(x2,y2,depth);
      glVertex3f(x2,y1,depth);
     glEnd(); 
 }  
 
void Draw_Texture(GLuint tex, float x1, float x2,float y1, float y2, float depth) 
{
 glBindTexture( GL_TEXTURE_2D, tex);  
 glBegin (GL_QUADS);
  glTexCoord2d(1.0,1.0);glVertex3f(x2,y2,depth);
  glTexCoord2d(0.0,1.0);glVertex3f(x1,y2,depth);
  glTexCoord2d(0.0,0.0);glVertex3f(x1,y1,depth);
  glTexCoord2d(1.0,0.0);glVertex3f(x2,y1,depth);
  glEnd();     
 } 

//------------------------------------------------------------------------------ 

