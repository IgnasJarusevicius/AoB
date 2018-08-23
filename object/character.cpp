#include "character.h"
#include "game.h"
#include <stdio.h>
#include "math.h"

//------------------------------------------------------------------------------
Character::~Character()
{
 
 delete path;                                       
 }
//------------------------------------------------------------------------------
void Character::Move(int xx,int yy)
{
         int i;
         Game::active_control = false; 
         Game::grid[xx][yy] = this;
         movement -= movement+1-Game::action_zone[xx][yy];
         
         while (1)
         {
         path->Add(GRID_X+xx*SLOT+SLOT/2,GRID_Y+yy*SLOT+SLOT/2);
         i = Game::action_zone[xx][yy];
         if ((xx>0)&&(yy>0)&&(Game::action_zone[xx-1][yy-1] == i+3)){
          xx--;yy--;path->first->dir = 1;continue;
          } 
         if ((xx>0)&&(yy< V_SLOT_NUMBER - 1)&&(Game::action_zone[xx-1][yy+1] == i+3)){
          xx--;yy++;path->first->dir = 7;continue;
          }
         if ((xx < H_SLOT_NUMBER - 1)&&(yy>0)&&(Game::action_zone[xx+1][yy-1] == i+3)){
          xx++;yy--;path->first->dir = 3;continue;                                                     
          }
         if ((xx < H_SLOT_NUMBER - 1)&&(yy < V_SLOT_NUMBER - 1)&&(Game::action_zone[xx+1][yy+1] == i+3)){
          xx++;yy++;path->first->dir = 5;continue;                                                     
          }
         if ((xx>0)&&(Game::action_zone[xx-1][yy] == i+2)){
          xx--;path->first->dir = 0;continue;
          } 
         if ((yy< V_SLOT_NUMBER - 1)&&(Game::action_zone[xx][yy+1] == i+2)){
          yy++;path->first->dir = 6;continue;
          }
         if ((yy>0)&&(Game::action_zone[xx][yy-1] == i+2)){
          yy--;path->first->dir = 2;continue;                                                     
          }
         if ((xx < H_SLOT_NUMBER - 1)&&(Game::action_zone[xx+1][yy] == i+2)){
          xx++;path->first->dir = 4;continue;                                                     
          } 
         Game::grid[xx][yy] = NULL;
         path->Remove();
         direction = path->first->dir;
         image_speed = 0.06*speed;
         state = 1;  
         Audio::Play(sounds[1]);
         break;
         } 
 }

//------------------------------------------------------------------------------
bool Character::Attack(Character* obj)
{
         int xx,yy, dir, targetx,targety, dist(0);
         
         xx = (int)(obj->x-GRID_X)/SLOT;
         yy = (int)(obj->y-GRID_Y)/SLOT;
         Game::active_control = false;
         
         if ((xx>0)&&(yy>0)&&(Game::action_zone[xx-1][yy-1] > dist)){
          dir = 1;targetx = xx-1;targety = yy-1;dist = Game::action_zone[xx-1][yy-1];
          } 
        
         if ((xx>0)&&(yy< V_SLOT_NUMBER - 1)&&(Game::action_zone[xx-1][yy+1] > dist)){
          dir = 7;targetx = xx-1;targety = yy+1;dist = Game::action_zone[xx-1][yy+1];
          }

         if ((xx < H_SLOT_NUMBER - 1)&&(yy>0)&&(Game::action_zone[xx+1][yy-1] > dist)){
          dir = 3;targetx = xx+1;targety = yy-1;dist = Game::action_zone[xx+1][yy-1];                                                     
          }
         if ((xx < H_SLOT_NUMBER - 1)&&(yy < V_SLOT_NUMBER - 1)&&(Game::action_zone[xx+1][yy+1] > dist)){
          dir = 5;targetx = xx+1;targety = yy+1;dist = Game::action_zone[xx+1][yy+1];                                                     
          }
         if ((xx>0)&&(Game::action_zone[xx-1][yy] > dist)){
          dir = 0;;targetx = xx-1;targety = yy;dist = Game::action_zone[xx-1][yy];
          }
         if ((yy< V_SLOT_NUMBER - 1)&&(Game::action_zone[xx][yy+1] > dist)){
          dir = 6;;targetx = xx;targety = yy+1;dist = Game::action_zone[xx][yy+1];
          }
         if ((yy>0)&&(Game::action_zone[xx][yy-1] > dist)){
          dir = 2;;targetx = xx;targety = yy-1;dist = Game::action_zone[xx][yy-1];                                                     
          }
         if ((xx < H_SLOT_NUMBER - 1)&&(Game::action_zone[xx+1][yy] > dist)){
          dir = 4;;targetx = xx+1;targety = yy;dist = Game::action_zone[xx+1][yy];                                                    
          }

         if (dist == 0) 
         {
          Game::active_control = true;
          return false;
          }
          else
          {
           target = (Character*)Game::grid[xx][yy];  
           if (dist > movement)
           {
            direction = dir;
            state = 2;
            image_index = 0.0f;
            image_speed = 0.5f;
            }
            else
            {
             path->Add(0.0f,0.0f);
             path->first->dir = dir;
             path->first->att = true;
             Move(targetx,targety); 
             }  
          } 
         return true;       
 }

//------------------------------------------------------------------------------ 
float Character::Speed_x(int dir)
{
 switch (dir)
 {
  case 0: return 1.0f*speed;
  case 1: case 7 : return 0.7071f*speed;
  case 2: case 6 : return 0.0f;
  case 3: case 5 : return -0.7071f*speed;
  case 4: return -1.0f*speed;      
  }
 }

//------------------------------------------------------------------------------ 
float Character::Speed_y(int dir)
{
 switch (dir)
 {
  case 0: case 4: return 0.0f;
  case 1: case 3 : return 0.7071f*speed;
  case 2: return 1.0f*speed;
  case 5: case 7 : return -0.7071f*speed;
  case 6: return -1.0f*speed;      
  }
 }

//------------------------------------------------------------------------------
void Character::Animation_End()
{
 if (state == 0)
 image_speed = 0.0f;
 
 if (state == 2)
 {
  state = 0;
  image_speed = 0.0f;
  if (!ranged)
  Game::active_control = true;  
  }
 
 if (state == 3)
 {
           image_speed = 0.0f;
           sprite = spriteset->sprites[3][direction];
           image_index = sprite->image_number-1;
           z = -1400.0f;
           }
 
 }

//------------------------------------------------------------------------------
void Character::Damage(int damage)
{
 damage = damage > 1 ? damage : 1;
 damage = damage < hp ? damage : hp;
 hp -= damage;
 if (player == 2)
 {
  if (Game::active->ranged)
  Stats::Damage(damage,true);
  else
  Stats::Damage(damage,false);
  }
 Damage_Report* obj = (Damage_Report*)Game::Create(21,x,y);
 char* str = new char[4];
 sprintf(str,"-%d",damage);
 obj->str = str;    
 }

//------------------------------------------------------------------------------
bool Character::Collision(float xx,float yy, int damage)
{
 if ( sqrt((xx-x)*(xx-x)+(yy-y)*(yy-y))<radius)
 {
  if (damage != 0)
  {
   damage = damage - (damage*def2)/100;
   Damage(damage);
   }
   return true;
  }
  else
  return false;
 }

//------------------------------------------------------------------------------
void Character::EndTurn()
{
 movement = maxmove;
 att = true;
 }

//------------------------------------------------------------------------------  
void Character::Att_End()
{
  int damage = dmg+rand()%(dmg2+1);
  damage = damage - (damage*target->def)/100; 
  target->Damage(damage); 
  Game::Select(this); 
  }

//------------------------------------------------------------------------------
void Character::Step()
{
 if ((state != 3)&&(hp < 1)){
                             state = 3;
                             Audio::Play(sounds[2]);
                             image_speed = 0.3f;
                             image_index = 0.0f;
                             if (player == 2)
                             {
                              Game::enemy_number -=1;
                              Stats::Die();
                              }
                             player = 0;
                             
                             Game::grid[(int)(x - GRID_X)/SLOT][(int)(y - GRID_Y)/SLOT]=NULL;
                             }     
 sprite = spriteset->sprites[state][direction];
 image_index += image_speed;
 if (image_index >= sprite->image_number)
 {
  image_index -= sprite->image_number;
  Animation_End();
  }  
 if (state == 0){
                 if (rand()%300 == 0)
                 image_speed = 0.25f;
                 } 
 if (state == 1){
                 x += Speed_x(direction);
                 y += Speed_y(direction);
                 if (fabs(x - path->first->x)+fabs(y - path->first->y) < speed)
                 {
                    x = path->first->x;
                    y = path->first->y;    
                    path->Remove();        
                    if (path->count > 0)
                    {              
                     direction = path->first->dir;
                     if (path->first->att)
                     {
                      state = 2;            
                      Audio::Stop(sounds[1]); 
                      image_index = 0;
                      path->Remove();
                      }                                                          
                     }
                    else
                    {
                     image_speed = 0.0f;
                     image_index = 0.0f;
                     state = 0;
                     Audio::Stop(sounds[1]); 
                     Game::Select(this);
                     Game::active_control = true;
                     }
                    }          
                    z = -y ;                  
                    } 
  if ((state == 2)&&(att)&&(!ranged)&&(image_index > 0.6f*sprite->image_number))
  { 
     att = false;
     Audio::Play(sounds[0]); 
     Att_End();
     }
 }
//------------------------------------------------------------------------------
