#ifndef GRES_H
#define GRES_H
#include <glad/glad.h>
enum
{
    NOTEXTURE = 0,
    GRASS,
    STONE,
    MENU,
    OKBUTTON,
    TITLE,
    ROCK1,
    ROCK2,
    TREE1,
    TEXTURES_CNT
};


class Sprite;
typedef Sprite* SpriteSet[4][8];

struct Tile
{
    Tile(){};
    Tile(GLuint t, float x0 = 0.0f, float x1 = 1.0f, float y0 = 0.0f, float y1 = 1.0f);
    Tile(GLuint t, float x0, float x1, float y0 , float y1, int w, int h);
    GLuint tex;
    float u0;
    float u1;
    float v0;
    float v1;
    int width;
    int height;
};



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
    static Sprite* arrow; 
    static GLuint textures[TEXTURES_CNT];        
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
