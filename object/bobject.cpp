#include "bobject.h"
#include "math.h"

//------------------------------------------------------------------------------
void Game_Object::Draw()
{ 
 if (player == 2)
 glColor3f(0.6f,0.6f,0.6f);
 else
 glColor3f(1.0f,1.0f,1.0f); 
 Draw_Texture(sprite->images[(int)floor(image_index)],x+sprite->x1,x+sprite->x2,y+sprite->y1,y+sprite->y2,z);  
 }
 
//------------------------------------------------------------------------------ 
bool Game_Object::Collision(float xx,float yy, int dmg)
{
 if ( sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y))<radius)
 return true;
 else
 return false;
 }
//------------------------------------------------------------------------------
