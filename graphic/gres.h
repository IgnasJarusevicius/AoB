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

typedef Sprite* SpriteSet[4][8];

class Graphic_Resources
{
 public:
    static SpriteSet orc_sprites;
    static SpriteSet pirate_sprites;
    static SpriteSet hunter_sprites;
    static SpriteSet skelarc_sprites;
    static SpriteSet skelwar_sprites;
    static SpriteSet barbar_sprites;
    static SpriteSet archer_sprites;
    static SpriteSet viking_sprites;
    static SpriteSet lava_sprites;
    static SpriteSet knight_sprites;
    static SpriteSet dwarf_sprites;
    static Sprite* sprites[SPRITES]; 
    static GLuint textures[TEXTURES];        
    static void Load_Graphics();      
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
 };  
#endif
