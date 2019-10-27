#include "texture.h"
#include "gres.h"
#include "sprite.h"
#include <iostream>

SpriteSet Graphic_Resources::orc_sprites;
SpriteSet Graphic_Resources::pirate_sprites;
SpriteSet Graphic_Resources::hunter_sprites;
SpriteSet Graphic_Resources::skelarc_sprites;
SpriteSet Graphic_Resources::skelwar_sprites;
SpriteSet Graphic_Resources::barbar_sprites;
SpriteSet Graphic_Resources::archer_sprites;
SpriteSet Graphic_Resources::viking_sprites;
SpriteSet Graphic_Resources::lava_sprites;
SpriteSet Graphic_Resources::knight_sprites;
SpriteSet Graphic_Resources::dwarf_sprites;

GLuint Graphic_Resources::textures[TEXTURES_CNT];
Sprite* Graphic_Resources::arrow;

Tile::Tile(GLuint t, float x0, float x1, float y0, float y1) :
    tex(t),
    u0(x0),
    u1(x1),
    v0(y0),
    v1(y1)
{
    glBindTexture(GL_TEXTURE_2D, tex);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    width *= u1-u0;
    height *= v1 -v0;
}

Tile::Tile(GLuint t, float x0, float x1, float y0, float y1, int w, int h) :
    tex(t),
    u0(x0),
    u1(x1),
    v0(y0),
    v1(y1),
    width(w),
    height(h)
{
}



void Graphic_Resources::Load_Graphics()
{
 Load_Textures();
 Load_Orc();
 Load_SkelArc();
 Load_SkelWar();
 Load_Hunter();
 Load_Pirate();
 Load_Barbar();
 Load_Archer();
 Load_Viking();
 Load_Lava();
 Load_Knight();
 Load_Dwarf();
 }

static std::vector<Tile> CreateTiles(unsigned tex, int width, int height)
{
    std::vector<Tile> tiles;
    int tex_width, tex_height;
    glBindTexture(GL_TEXTURE_2D, tex);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tex_width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &tex_height);
    for (int w = 0; w < tex_width; w += width)
    {
        const float u0 = (float)w/tex_width;
        const float u1 = (float)(w+width)/tex_width;
        for (int h = 0; h < tex_height; h += height)
        {
            float v0 = (float)(h)/tex_height;
            float v1 = (float)(h+height)/tex_height;
            tiles.push_back(Tile(tex, u0, u1, v0, v1, width, height));
        }
    }
    return tiles;
}

//------------------------------------------------------------------------------
void Graphic_Resources::Load_Orc()
{
    auto tiles1 = CreateTiles(Texture("img/orc/idle.png", true),96, 96);
    auto tiles2 = CreateTiles(Texture("img/orc/running.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/orc/attack.png", true), 96, 96);
    auto tiles4 = CreateTiles(Texture("img/orc/dying.png", true), 128, 128);
    for (int i = 0; i<8; i++)
    {
        orc_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        orc_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        orc_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        orc_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 64, 40);
    }
 }
//------------------------------------------------------------------------------
void Graphic_Resources::Load_SkelArc()
{
    auto tiles1 = CreateTiles(Texture("img/skel_arch/walking.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/skel_arch/attack.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/skel_arch/dying.png", true), 96, 96);
    for (int i = 0; i<8; i++)
    {
        skelarc_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        skelarc_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        skelarc_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        skelarc_sprites[0][i] = new Sprite(std::vector<Tile>(1, skelarc_sprites[2][i]->images[0]), 48, 24);
    }
 }
//------------------------------------------------------------------------------
void Graphic_Resources::Load_SkelWar()
{
    auto tiles1 = CreateTiles(Texture("img/skel_war/running.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/skel_war/attack.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/skel_war/dying.png", true), 96, 96);
    for (int i = 0; i<8; i++)
    {
        skelwar_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        skelwar_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        skelwar_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        skelwar_sprites[0][i] = new Sprite(std::vector<Tile>(1, skelwar_sprites[2][i]->images[0]), 48, 24);
    }
 }
//------------------------------------------------------------------------------
void Graphic_Resources::Load_Hunter()
{
    auto tiles1 = CreateTiles(Texture("img/hunter/idle.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/hunter/walking.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/hunter/attack.png", true), 96, 96);
    auto tiles4 = CreateTiles(Texture("img/hunter/dying.png", true), 128, 128);
    for (int i = 0; i<8; i++)
    {
        hunter_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        hunter_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        hunter_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        hunter_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 64, 40);
    }
 }

void Graphic_Resources::Load_Pirate()
{
    auto tiles1 = CreateTiles(Texture("img/pirate/running.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/pirate/attack.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/pirate/dying.png", true), 96, 96);
    for (int i = 0; i<8; i++)
    {
        pirate_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        pirate_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        pirate_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles3[i/2*tiles3.size()/4], &tiles3[(i/2+1)*tiles3.size()/4]), 48, 24);
        pirate_sprites[0][i] = new Sprite(std::vector<Tile>(1, pirate_sprites[2][i]->images[0]), 48, 24);
    }
 }

void Graphic_Resources::Load_Barbar()
{
    auto tiles1 = CreateTiles(Texture("img/barbar/running.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/barbar/attack.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/barbar/dying.png", true), 96, 96);
    for (int i = 0; i<8; i++)
    {
        barbar_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        barbar_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        barbar_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        barbar_sprites[0][i] = new Sprite(std::vector<Tile>(1, barbar_sprites[2][i]->images[0]), 48, 24);
    }
 }

void Graphic_Resources::Load_Archer()
{
    auto tiles1 = CreateTiles(Texture("img/archer/walking.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/archer/shooting.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/archer/dying.png", true), 128, 128);

    for (int i = 0; i<8; i++)
    {
        archer_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        archer_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        archer_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 64, 40);
        archer_sprites[0][i] = new Sprite(std::vector<Tile>(1, archer_sprites[2][i]->images[0]), 48, 24);
    }
 }

void Graphic_Resources::Load_Viking()
{
    auto tiles1 = CreateTiles(Texture("img/viking/idle.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/viking/running.png", true), 128, 128);
    auto tiles3 = CreateTiles(Texture("img/viking/attack.png", true), 128, 128);
    auto tiles4 = CreateTiles(Texture("img/viking/dying.png", true), 128, 128);
    for (int i = 0; i<8; i++)
    {
        viking_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        viking_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 64, 40);
        viking_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 64, 40);
        viking_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 64, 40);
    }
 }

void Graphic_Resources::Load_Lava()
{
    auto tiles1 = CreateTiles(Texture("img/lava/idle.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/lava/walking.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/lava/attack.png", true), 96, 96);
    auto tiles4 = CreateTiles(Texture("img/lava/dying.png", true), 96, 96);
    for (int i = 0; i<8; i++)
    {
        lava_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        lava_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        lava_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        lava_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 48, 24);
    }
 }

void Graphic_Resources::Load_Knight()
{
    auto tiles1 = CreateTiles(Texture("img/knight/idle.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/knight/walking.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/knight/attack.png", true), 96, 96);
    auto tiles4 = CreateTiles(Texture("img/knight/dying.png", true), 128, 128);
    for (int i = 0; i<8; i++)
    {
        knight_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        knight_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        knight_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 48, 24);
        knight_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 64, 40);
    }
 }

void Graphic_Resources::Load_Dwarf()
{
    auto tiles1 = CreateTiles(Texture("img/dwarf/idle.png", true), 96, 96);
    auto tiles2 = CreateTiles(Texture("img/dwarf/walking.png", true), 96, 96);
    auto tiles3 = CreateTiles(Texture("img/dwarf/attack.png", true), 128, 128);
    auto tiles4 = CreateTiles(Texture("img/dwarf/dying.png", true), 128, 128);
    for (int i = 0; i<8; i++)
    {
        dwarf_sprites[0][i] = new Sprite(std::vector<Tile>(&tiles1[i*tiles1.size()/8], &tiles1[(i+1)*tiles1.size()/8]), 48, 24);
        dwarf_sprites[1][i] = new Sprite(std::vector<Tile>(&tiles2[i*tiles2.size()/8], &tiles2[(i+1)*tiles2.size()/8]), 48, 24);
        dwarf_sprites[2][i] = new Sprite(std::vector<Tile>(&tiles3[i*tiles3.size()/8], &tiles3[(i+1)*tiles3.size()/8]), 64, 40);
        dwarf_sprites[3][i] = new Sprite(std::vector<Tile>(&tiles4[i*tiles4.size()/8], &tiles4[(i+1)*tiles4.size()/8]), 64, 40);
    }
 }

void Graphic_Resources::Load_Textures()
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    uint32_t data = 0;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data);
    textures[NOTEXTURE] = texture;

    textures[GRASS] = Texture("img/back/grass.bmp", false);
    textures[STONE] = Texture("img/back/stone.bmp", false);
    textures[MENU]= Texture("img/menu/menu1.bmp", false);
    textures[OKBUTTON]= Texture("img/menu/okbutton.bmp", false);
    textures[TITLE]= Texture("img/menu/title.bmp", false);
    GLuint tex1 = Texture("img/arrow/arrow.png", true);
    arrow = new Sprite(CreateTiles(tex1, 32, 64), 16, 18);
    textures[TREE1] = Texture("img/obs/tree_100.bmp", true);
    textures[ROCK1] = Texture("img/obs/rock_100.bmp", true);
    textures[ROCK2] = Texture("img/obs/rock_200.bmp", true);
}

