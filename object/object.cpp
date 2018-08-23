#include <GL/gl.h>
#include <GL/freeglut.h>
#include "object.h"
#include <stdio.h>
//------------------------------------------------------------------------------    
Skel_Arch::Skel_Arch(float set_x,float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = true;
 hp = 40;
 maxhp = 40;
 dmg = 13;
 dmg2 = 6;
 def = 0;
 def2 = 85;
 state = 0;
 direction = 0;
 speed = 5;
 radius = 16;
 maxmove = 6;
 spriteset = Graphic_Resources::spritesets[SKELARC];
 sounds[0] = PLAY_BOW;
 sounds[1] = PLAY_STEP;
 sounds[2] = PLAY_DIE2;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;    
 EndTurn();             
 }

//------------------------------------------------------------------------------     
Hunter::Hunter(float set_x,float set_y)
{
 
 x = set_x;
 y = set_y;
 z = -y;
 ranged = true;
 hp = 40;
 maxhp = 40;
 dmg = 7;
 dmg2 = 7;
 def = 0;
 def2 = 0;
 state = 0;
 direction = 0;
 speed = 6;
 radius = 16;
 maxmove = 7;
 sounds[0] = PLAY_BOW;
 sounds[1] = PLAY_STEP2;
 sounds[2] = PLAY_DIE;
 spriteset = Graphic_Resources::spritesets[HUNTER];
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;    
 EndTurn();                 
 }

//------------------------------------------------------------------------------    
Orc::Orc(float set_x, float set_y)
{
 
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 60;
 maxhp = 60;
 dmg = 8;
 dmg2 = 4;
 def = 10;
 def2 = 0;
 state = 0;
 direction = 0;
 speed = 7;
 maxmove = 10;
 radius = 16;
 sounds[0] = PLAY_ATT;
 sounds[1] = PLAY_STEP3;
 sounds[2] = PLAY_DIE;
 spriteset = Graphic_Resources::spritesets[ORC];;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 }

//------------------------------------------------------------------------------    
Skel_War::Skel_War(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 50;
 maxhp = 50;
 dmg = 16;
 dmg2 = 4;
 def = 20;
 def2 = 85;
 state = 0;
 direction = 0;
 speed = 6;
 maxmove = 8;
 sounds[0] = PLAY_SWORD;
 sounds[1] = PLAY_STEP2;
 sounds[2] = PLAY_DIE2;
 radius = 16;
 spriteset = Graphic_Resources::spritesets[SKELWAR];;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 } 

//------------------------------------------------------------------------------     
Pirate::Pirate(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 50;
 maxhp = 50;
 dmg = 11;
 dmg2 = 2;
 def = 0;
 def2 = 0;
 state = 0;
 direction = 0;
 speed = 8;
 radius = 16;
 maxmove = 12;
 sounds[0] = PLAY_ATT;
 sounds[1] = PLAY_STEP4;
 sounds[2] = PLAY_DIE;
 spriteset = Graphic_Resources::spritesets[PIRATE];;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 }
 
//------------------------------------------------------------------------------    
Barbar::Barbar(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 80;
 maxhp = 80;
 dmg = 17;
 dmg2 = 8;
 def = 0;
 def2 = 0;
 state = 0;
 direction = 0;
 speed = 8;
 radius = 16;
 maxmove = 11;
 spriteset = Graphic_Resources::spritesets[BARBAR];;
 sounds[0] = PLAY_AXE;
 sounds[1] = PLAY_STEP4;
 sounds[2] = PLAY_DIE;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 }
 
//------------------------------------------------------------------------------     
Viking::Viking(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 100;
 maxhp = 100;
 dmg = 23;
 dmg2 = 6;
 def = 50;
 def2 = 25;
 state = 0;
 direction = 0;
 speed = 7;
 radius = 16;
 maxmove = 9;
 spriteset = Graphic_Resources::spritesets[VIKING];;
 sounds[0] = PLAY_SWORD;
 sounds[1] = PLAY_STEP3;
 sounds[2] = PLAY_DIE;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 }
 
//------------------------------------------------------------------------------     
Lava::Lava(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 150;
 maxhp = 150;
 dmg = 20;
 dmg2 = 10;
 def = 10;
 def2 = 40;
 state = 0;
 direction = 0;
 speed = 6;
 radius = 16;
 maxmove = 8;
 spriteset = Graphic_Resources::spritesets[LAVA];;
 sounds[0] = PLAY_WHIP;
 sounds[1] = PLAY_STEP2;
 sounds[2] = PLAY_DIE2;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;
 EndTurn(); 
 }

//------------------------------------------------------------------------------     
Archer::Archer(float set_x,float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = true;
 hp = 70;
 maxhp = 70;
 dmg = 25;
 dmg2 = 5;
 def = 10;
 def2 = 20;
 state = 0;
 direction = 0;
 speed = 6;
 radius = 16;
 maxmove = 8;
 spriteset = Graphic_Resources::spritesets[ARCHER];;
 sounds[0] = PLAY_BOW;
 sounds[1] = PLAY_STEP2;
 sounds[2] = PLAY_DIE;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;    
 EndTurn();              
 }

//------------------------------------------------------------------------------     
Knight::Knight(float set_x,float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 90;
 maxhp = 90;
 dmg = 24;
 dmg2 = 3;
 def = 70;
 def2 = 70;
 state = 0;
 direction = 0;
 speed = 6;
 radius = 16;
 maxmove = 8;
 spriteset = Graphic_Resources::spritesets[KNIGHT];;
 sounds[0] = PLAY_SWORD;
 sounds[1] = PLAY_STEP2;
 sounds[2] = PLAY_DIE;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;    
 EndTurn();                  
 }

//------------------------------------------------------------------------------     
Dwarf::Dwarf(float set_x,float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 ranged = false;
 hp = 120;
 maxhp = 120;
 dmg = 28;
 dmg2 = 14;
 def = 30;
 def2 = 60;
 state = 0;
 direction = 0;
 speed = 7;
 radius = 16;
 maxmove = 10;
 spriteset = Graphic_Resources::spritesets[DWARF];;
 sounds[0] = PLAY_AXE;
 sounds[1] = PLAY_STEP3;
 sounds[2] = PLAY_DIE;
 image_speed = 0.0f;
 image_index = 0.0f;
 path = new Path;    
 EndTurn();             
 }

//------------------------------------------------------------------------------      
Tree::Tree(float set_x, float set_y)
{
 x = set_x;
 y = set_y;
 z = 16.0f-y;
 image_speed = 0.0f;
 image_index = 0.0f;
 radius = 12.0f;
 player = 0;
 sprite = Graphic_Resources::sprites[TREE1];         
 }

//------------------------------------------------------------------------------    
Rock::Rock(float set_x,float set_y)
{
 x = set_x;
 y = set_y;
 z = -y;
 image_speed = 0.0f;
 image_index = 0.0f;
 radius = 24;
 player = 0; 
 sprite = Graphic_Resources::sprites[ROCK1];                    
 }
//------------------------------------------------------------------------------    

 
