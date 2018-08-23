#include "ranged.h"
#include "game.h"
#include "math.h"
#include "audio.h"
#define _USE_MATH_DEFINES

//------------------------------------------------------------------------------
bool Ranged::Attack(Character* target)
{
 Arrow* obj;
 float dir;
 Game::active_control = false;
 state = 2;
 image_speed = 0.3f;
 image_index = 0.0f;
 obj = (Arrow*)Game::Create(20,x,y);
 dir = atan2(target->y-y,target->x-x);
 obj->xspeed = 2.0f*cos(dir);
 obj->yspeed = 2.0f*sin(dir);
 obj->shooter = this;
 obj->delay = 16;
 obj->dmg = dmg+rand()%(dmg2+1);  
 if (dir < -0.875f*M_PI)
 direction = 4;
 else if (dir < -0.625f*M_PI)
      direction = 5;
      else if (dir < -0.375f*M_PI)
           direction = 6;
           else if (dir < -0.125f*M_PI)
                direction = 7;
                else if (dir < 0.125f*M_PI)
                     direction = 0;
                     else if (dir < 0.375f*M_PI)
                          direction = 1;
                          else if (dir < 0.625f*M_PI)
                               direction = 2;
                               else if (dir < 0.875f*M_PI)
                                    direction = 3;
                                    else direction = 4;      
 obj->image_index = 0;
 for (int i = 1;i<32;i++)
 if (dir <= (i-15)*M_PI/16.0f-M_PI/32.0f)
 {
   obj->image_index = i; 
   break;          
   } 
 return 1;
 } 

//------------------------------------------------------------------------------
Arrow::Arrow(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 player = 0;
 sprite = Graphic_Resources::sprites[ARROW];
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
   Audio::Play(shooter->sounds[0]); 
   shooter->att = false;              //fixing bugs
   }         
  delay--;         
  return;
  }    
      
 for (int i = 0; i< 10;i++)
 {          
  x += xspeed;
  y += yspeed; 
  if ((obj = Game::grid[(int)(x - GRID_X)/SLOT][(int)(y - GRID_Y)/SLOT]) != NULL)
  if (obj != shooter) 
  if (obj->Collision(x,y,dmg)) 
  {  
   Audio::Play(PLAY_HIT); 
   Game::active_control = true;                                  
   Game::Remove(this);
   break;
   }
  }    
 }
//------------------------------------------------------------------------------
 
