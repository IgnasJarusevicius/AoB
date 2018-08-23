#ifndef GRES_H
#define GRES_H
#include "sprite.h"

#define TEXTURES 5
#define GRASS 0
#define STONE 1
#define MENU 2
#define OKBUTTON 3
#define TITLE 4

#define SPRITES 3
#define ARROW 0
#define ROCK1 1
#define TREE1 2

#define SPRITESETS 11
#define ORC 0
#define PIRATE 1
#define HUNTER 2
#define SKELARC 3
#define SKELWAR 4
#define BARBAR 5
#define ARCHER 6
#define VIKING 7
#define LAVA 8
#define KNIGHT 9
#define DWARF 10


class Graphic_Resources
{
 public: static SpriteSet* spritesets[SPRITESETS];
         static Sprite* sprites[SPRITES]; 
         static GLuint textures[TEXTURES];        
         static void Load_Graphics(); 
         static void Delete_All();       
private: 
         static void Load_Textures();
         static void Load_Orc();
         static void Load_SkelArc();
         static void Load_SkelWar();
         static void Load_Hunter();
         static void Load_Pirate();
         static void Load_Barbar();
         static void Load_Archer();
         static void Load_Viking();
         static void Load_Lava();
         static void Load_Knight();
         static void Load_Dwarf();
         static GLuint LoadTexture(const char *);                     
 };  
#endif
