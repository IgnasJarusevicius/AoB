#include "gres.h"
#include <stdio.h>
#include <stdint.h>

SpriteSet* Graphic_Resources::spritesets[SPRITESETS];
GLuint Graphic_Resources::textures[TEXTURES];
Sprite* Graphic_Resources::sprites[SPRITES];
 
//------------------------------------------------------------------------------ 
GLuint Graphic_Resources::LoadTexture(const char * filename)
{
    GLuint texture;
    uint32_t width, height, size;
    unsigned char * data;
    FILE * file;
    
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    
    fseek(file,18,SEEK_SET);
    fread(&width, sizeof(width),1,file);
    fread(&height, sizeof(height),1,file);
    size = width * height * 3; 
    fseek(file,28,SEEK_CUR);
    data = new unsigned char[size];
    fread( data,size, 1, file );
    fclose( file );
    
   	unsigned char tmp;					
	for( int i(0); i < size; i += 3 )
	{
		tmp = data[i];
		data[i] = data[i+2];
		data[i+2] = tmp;
	}
	
    glGenTextures( 1, &texture ); 
    glBindTexture( GL_TEXTURE_2D, texture ); 
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexImage2D( GL_TEXTURE_2D,0, 3, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, data );
    delete[] data;
    return texture; 
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
//------------------------------------------------------------------------------ 
void Graphic_Resources::Delete_All()
{
 for (int i = 0; i < SPRITESETS; i++)
 delete spritesets[i];
 for (int i = 0; i < SPRITES; i++)
 delete sprites[i];
 glDeleteTextures( TEXTURES, textures);
 }
//------------------------------------------------------------------------------
void Graphic_Resources::Load_Orc()
{
 spritesets[ORC] = new SpriteSet();
 
 spritesets[ORC]->sprites[0][0] = new Sprite("img/orc/paused e00",9);
 spritesets[ORC]->sprites[0][1] = new Sprite("img/orc/paused ne00",9);
 spritesets[ORC]->sprites[0][2] = new Sprite("img/orc/paused n00",9);
 spritesets[ORC]->sprites[0][3] = new Sprite("img/orc/paused nw00",9);
 spritesets[ORC]->sprites[0][4] = new Sprite("img/orc/paused w00",9);
 spritesets[ORC]->sprites[0][5] = new Sprite("img/orc/paused sw00",9);
 spritesets[ORC]->sprites[0][6] = new Sprite("img/orc/paused s00",9);
 spritesets[ORC]->sprites[0][7] = new Sprite("img/orc/paused se00",9);

 spritesets[ORC]->sprites[1][0] = new Sprite("img/orc/running e00",8);
 spritesets[ORC]->sprites[1][1] = new Sprite("img/orc/running ne00",8);
 spritesets[ORC]->sprites[1][2] = new Sprite("img/orc/running n00",8);
 spritesets[ORC]->sprites[1][3] = new Sprite("img/orc/running nw00",8);
 spritesets[ORC]->sprites[1][4] = new Sprite("img/orc/running w00",8);
 spritesets[ORC]->sprites[1][5] = new Sprite("img/orc/running sw00",8);
 spritesets[ORC]->sprites[1][6] = new Sprite("img/orc/running s00",8);
 spritesets[ORC]->sprites[1][7] = new Sprite("img/orc/running se00",8);
 
 spritesets[ORC]->sprites[2][0] = new Sprite("img/orc/attack e00",13);
 spritesets[ORC]->sprites[2][1] = new Sprite("img/orc/attack ne00",13);
 spritesets[ORC]->sprites[2][2] = new Sprite("img/orc/attack n00",13);
 spritesets[ORC]->sprites[2][3] = new Sprite("img/orc/attack nw00",13);
 spritesets[ORC]->sprites[2][4] = new Sprite("img/orc/attack w00",13);
 spritesets[ORC]->sprites[2][5] = new Sprite("img/orc/attack sw00",13);
 spritesets[ORC]->sprites[2][6] = new Sprite("img/orc/attack s00",13);
 spritesets[ORC]->sprites[2][7] = new Sprite("img/orc/attack se00",13);
 
 spritesets[ORC]->sprites[3][0] = new Sprite("img/orc/tipping over e00",12);
 spritesets[ORC]->sprites[3][1] = new Sprite("img/orc/tipping over ne00",12);
 spritesets[ORC]->sprites[3][2] = new Sprite("img/orc/tipping over n00",12);
 spritesets[ORC]->sprites[3][3] = new Sprite("img/orc/tipping over nw00",12);
 spritesets[ORC]->sprites[3][4] = new Sprite("img/orc/tipping over w00",12);
 spritesets[ORC]->sprites[3][5] = new Sprite("img/orc/tipping over sw00",12);
 spritesets[ORC]->sprites[3][6] = new Sprite("img/orc/tipping over s00",12);
 spritesets[ORC]->sprites[3][7] = new Sprite("img/orc/tipping over se00",12);
 }
//------------------------------------------------------------------------------ 
void Graphic_Resources::Load_SkelArc()
{
 spritesets[SKELARC] = new SpriteSet();

 spritesets[SKELARC]->sprites[1][0] = new Sprite("img/skel_arch/walking e00",8);
 spritesets[SKELARC]->sprites[1][1] = new Sprite("img/skel_arch/walking ne00",8);
 spritesets[SKELARC]->sprites[1][2] = new Sprite("img/skel_arch/walking n00",8);
 spritesets[SKELARC]->sprites[1][3] = new Sprite("img/skel_arch/walking nw00",8);
 spritesets[SKELARC]->sprites[1][4] = new Sprite("img/skel_arch/walking w00",8);
 spritesets[SKELARC]->sprites[1][5] = new Sprite("img/skel_arch/walking sw00",8);
 spritesets[SKELARC]->sprites[1][6] = new Sprite("img/skel_arch/walking s00",8);
 spritesets[SKELARC]->sprites[1][7] = new Sprite("img/skel_arch/walking se00",8);
 
 spritesets[SKELARC]->sprites[2][0] = new Sprite("img/skel_arch/shooting e00",13);
 spritesets[SKELARC]->sprites[2][1] = new Sprite("img/skel_arch/shooting ne00",13);
 spritesets[SKELARC]->sprites[2][2] = new Sprite("img/skel_arch/shooting n00",13);
 spritesets[SKELARC]->sprites[2][3] = new Sprite("img/skel_arch/shooting nw00",13);
 spritesets[SKELARC]->sprites[2][4] = new Sprite("img/skel_arch/shooting w00",13);
 spritesets[SKELARC]->sprites[2][5] = new Sprite("img/skel_arch/shooting sw00",13);
 spritesets[SKELARC]->sprites[2][6] = new Sprite("img/skel_arch/shooting s00",13);
 spritesets[SKELARC]->sprites[2][7] = new Sprite("img/skel_arch/shooting se00",13);
 
 spritesets[SKELARC]->sprites[0][0] = new Sprite(spritesets[SKELARC]->sprites[2][0],0);
 spritesets[SKELARC]->sprites[0][1] = new Sprite(spritesets[SKELARC]->sprites[2][1],0);
 spritesets[SKELARC]->sprites[0][2] = new Sprite(spritesets[SKELARC]->sprites[2][2],0);
 spritesets[SKELARC]->sprites[0][3] = new Sprite(spritesets[SKELARC]->sprites[2][3],0);
 spritesets[SKELARC]->sprites[0][4] = new Sprite(spritesets[SKELARC]->sprites[2][4],0);
 spritesets[SKELARC]->sprites[0][5] = new Sprite(spritesets[SKELARC]->sprites[2][5],0);
 spritesets[SKELARC]->sprites[0][6] = new Sprite(spritesets[SKELARC]->sprites[2][6],0);
 spritesets[SKELARC]->sprites[0][7] = new Sprite(spritesets[SKELARC]->sprites[2][7],0);
 
 spritesets[SKELARC]->sprites[3][0] = new Sprite("img/skel_arch/disintegrate e00",9);
 spritesets[SKELARC]->sprites[3][1] = new Sprite("img/skel_arch/disintegrate ne00",9);
 spritesets[SKELARC]->sprites[3][2] = new Sprite("img/skel_arch/disintegrate n00",9);
 spritesets[SKELARC]->sprites[3][3] = new Sprite("img/skel_arch/disintegrate nw00",9);
 spritesets[SKELARC]->sprites[3][4] = new Sprite("img/skel_arch/disintegrate w00",9);
 spritesets[SKELARC]->sprites[3][5] = new Sprite("img/skel_arch/disintegrate sw00",9);
 spritesets[SKELARC]->sprites[3][6] = new Sprite("img/skel_arch/disintegrate s00",9);
 spritesets[SKELARC]->sprites[3][7] = new Sprite("img/skel_arch/disintegrate se00",9);
 }
//------------------------------------------------------------------------------ 
void Graphic_Resources::Load_SkelWar()
{
 spritesets[SKELWAR] = new SpriteSet();

 spritesets[SKELWAR]->sprites[1][0] = new Sprite("img/skel_war/run_e00",9);
 spritesets[SKELWAR]->sprites[1][1] = new Sprite("img/skel_war/run_ne00",9);
 spritesets[SKELWAR]->sprites[1][2] = new Sprite("img/skel_war/run_n00",9);
 spritesets[SKELWAR]->sprites[1][3] = new Sprite("img/skel_war/run_nw00",9);
 spritesets[SKELWAR]->sprites[1][4] = new Sprite("img/skel_war/run_w00",9);
 spritesets[SKELWAR]->sprites[1][5] = new Sprite("img/skel_war/run_sw00",9);
 spritesets[SKELWAR]->sprites[1][6] = new Sprite("img/skel_war/run_s00",9);
 spritesets[SKELWAR]->sprites[1][7] = new Sprite("img/skel_war/run_se00",9);
 
 spritesets[SKELWAR]->sprites[2][0] = new Sprite("img/skel_war/attack e00",10);
 spritesets[SKELWAR]->sprites[2][1] = new Sprite("img/skel_war/attack ne00",10);
 spritesets[SKELWAR]->sprites[2][2] = new Sprite("img/skel_war/attack n00",10);
 spritesets[SKELWAR]->sprites[2][3] = new Sprite("img/skel_war/attack nw00",10);
 spritesets[SKELWAR]->sprites[2][4] = new Sprite("img/skel_war/attack w00",10);
 spritesets[SKELWAR]->sprites[2][5] = new Sprite("img/skel_war/attack sw00",10);
 spritesets[SKELWAR]->sprites[2][6] = new Sprite("img/skel_war/attack s00",10);
 spritesets[SKELWAR]->sprites[2][7] = new Sprite("img/skel_war/attack se00",10);
 
 spritesets[SKELWAR]->sprites[0][0] = new Sprite(spritesets[SKELWAR]->sprites[2][0],0);
 spritesets[SKELWAR]->sprites[0][1] = new Sprite(spritesets[SKELWAR]->sprites[2][1],0);
 spritesets[SKELWAR]->sprites[0][2] = new Sprite(spritesets[SKELWAR]->sprites[2][2],0);
 spritesets[SKELWAR]->sprites[0][3] = new Sprite(spritesets[SKELWAR]->sprites[2][3],0);
 spritesets[SKELWAR]->sprites[0][4] = new Sprite(spritesets[SKELWAR]->sprites[2][4],0);
 spritesets[SKELWAR]->sprites[0][5] = new Sprite(spritesets[SKELWAR]->sprites[2][5],0);
 spritesets[SKELWAR]->sprites[0][6] = new Sprite(spritesets[SKELWAR]->sprites[2][6],0);
 spritesets[SKELWAR]->sprites[0][7] = new Sprite(spritesets[SKELWAR]->sprites[2][7],0);
 
 spritesets[SKELWAR]->sprites[3][0] = new Sprite("img/skel_war/die_e00",9);
 spritesets[SKELWAR]->sprites[3][1] = new Sprite("img/skel_war/die_ne00",9);
 spritesets[SKELWAR]->sprites[3][2] = new Sprite("img/skel_war/die_n00",9);
 spritesets[SKELWAR]->sprites[3][3] = new Sprite("img/skel_war/die_nw00",9);
 spritesets[SKELWAR]->sprites[3][4] = new Sprite("img/skel_war/die_w00",9);
 spritesets[SKELWAR]->sprites[3][5] = new Sprite("img/skel_war/die_sw00",9);
 spritesets[SKELWAR]->sprites[3][6] = new Sprite("img/skel_war/die_s00",9);
 spritesets[SKELWAR]->sprites[3][7] = new Sprite("img/skel_war/die_se00",9);
 }
//------------------------------------------------------------------------------ 
void Graphic_Resources::Load_Hunter()
{
 spritesets[HUNTER] = new SpriteSet();
 
 spritesets[HUNTER]->sprites[0][0] = new Sprite("img/hunter/looking e00",13);
 spritesets[HUNTER]->sprites[0][1] = new Sprite("img/hunter/looking ne00",13);
 spritesets[HUNTER]->sprites[0][2] = new Sprite("img/hunter/looking n00",13);
 spritesets[HUNTER]->sprites[0][3] = new Sprite("img/hunter/looking nw00",13);
 spritesets[HUNTER]->sprites[0][4] = new Sprite("img/hunter/looking w00",13);
 spritesets[HUNTER]->sprites[0][5] = new Sprite("img/hunter/looking sw00",13);
 spritesets[HUNTER]->sprites[0][6] = new Sprite("img/hunter/looking s00",13);
 spritesets[HUNTER]->sprites[0][7] = new Sprite("img/hunter/looking se00",13);

 spritesets[HUNTER]->sprites[1][0] = new Sprite("img/hunter/walking e00",8);
 spritesets[HUNTER]->sprites[1][1] = new Sprite("img/hunter/walking ne00",8);
 spritesets[HUNTER]->sprites[1][2] = new Sprite("img/hunter/walking n00",8);
 spritesets[HUNTER]->sprites[1][3] = new Sprite("img/hunter/walking nw00",8);
 spritesets[HUNTER]->sprites[1][4] = new Sprite("img/hunter/walking w00",8);
 spritesets[HUNTER]->sprites[1][5] = new Sprite("img/hunter/walking sw00",8);
 spritesets[HUNTER]->sprites[1][6] = new Sprite("img/hunter/walking s00",8);
 spritesets[HUNTER]->sprites[1][7] = new Sprite("img/hunter/walking se00",8);
 
 spritesets[HUNTER]->sprites[2][0] = new Sprite("img/hunter/shooting e00",13);
 spritesets[HUNTER]->sprites[2][1] = new Sprite("img/hunter/shooting ne00",13);
 spritesets[HUNTER]->sprites[2][2] = new Sprite("img/hunter/shooting n00",13);
 spritesets[HUNTER]->sprites[2][3] = new Sprite("img/hunter/shooting nw00",13);
 spritesets[HUNTER]->sprites[2][4] = new Sprite("img/hunter/shooting w00",13);
 spritesets[HUNTER]->sprites[2][5] = new Sprite("img/hunter/shooting sw00",13);
 spritesets[HUNTER]->sprites[2][6] = new Sprite("img/hunter/shooting s00",13);
 spritesets[HUNTER]->sprites[2][7] = new Sprite("img/hunter/shooting se00",13);
 
 spritesets[HUNTER]->sprites[3][0] = new Sprite("img/hunter/tipping over e00",11);
 spritesets[HUNTER]->sprites[3][1] = new Sprite("img/hunter/tipping over ne00",11);
 spritesets[HUNTER]->sprites[3][2] = new Sprite("img/hunter/tipping over n00",11);
 spritesets[HUNTER]->sprites[3][3] = new Sprite("img/hunter/tipping over nw00",11);
 spritesets[HUNTER]->sprites[3][4] = new Sprite("img/hunter/tipping over w00",11);
 spritesets[HUNTER]->sprites[3][5] = new Sprite("img/hunter/tipping over sw00",11);
 spritesets[HUNTER]->sprites[3][6] = new Sprite("img/hunter/tipping over s00",11);
 spritesets[HUNTER]->sprites[3][7] = new Sprite("img/hunter/tipping over se00",11);
 }
 
void Graphic_Resources::Load_Pirate()
{
 spritesets[PIRATE] = new SpriteSet();

 spritesets[PIRATE]->sprites[1][0] = new Sprite("img/pirate/rennt e00",9);
 spritesets[PIRATE]->sprites[1][1] = new Sprite("img/pirate/rennt ne00",9);
 spritesets[PIRATE]->sprites[1][2] = new Sprite("img/pirate/rennt n00",9);
 spritesets[PIRATE]->sprites[1][3] = new Sprite("img/pirate/rennt nw00",9);
 spritesets[PIRATE]->sprites[1][4] = new Sprite("img/pirate/rennt w00",9);
 spritesets[PIRATE]->sprites[1][5] = new Sprite("img/pirate/rennt sw00",9);
 spritesets[PIRATE]->sprites[1][6] = new Sprite("img/pirate/rennt s00",9);
 spritesets[PIRATE]->sprites[1][7] = new Sprite("img/pirate/rennt se00",9);
 
 spritesets[PIRATE]->sprites[2][0] = new Sprite("img/pirate/attack e00",13);
 spritesets[PIRATE]->sprites[2][1] = new Sprite("img/pirate/attack ne00",13);
 spritesets[PIRATE]->sprites[2][2] = new Sprite("img/pirate/attack n00",13);
 spritesets[PIRATE]->sprites[2][3] = new Sprite("img/pirate/attack nw00",13);
 spritesets[PIRATE]->sprites[2][4] = new Sprite("img/pirate/attack w00",13);
 spritesets[PIRATE]->sprites[2][5] = new Sprite("img/pirate/attack sw00",13);
 spritesets[PIRATE]->sprites[2][6] = new Sprite("img/pirate/attack s00",13);
 spritesets[PIRATE]->sprites[2][7] = new Sprite("img/pirate/attack se00",13);
 
 spritesets[PIRATE]->sprites[0][0] = new Sprite(spritesets[PIRATE]->sprites[2][0],0);
 spritesets[PIRATE]->sprites[0][1] = new Sprite(spritesets[PIRATE]->sprites[2][1],0);
 spritesets[PIRATE]->sprites[0][2] = new Sprite(spritesets[PIRATE]->sprites[2][2],0);
 spritesets[PIRATE]->sprites[0][3] = new Sprite(spritesets[PIRATE]->sprites[2][3],0);
 spritesets[PIRATE]->sprites[0][4] = new Sprite(spritesets[PIRATE]->sprites[2][4],0);
 spritesets[PIRATE]->sprites[0][5] = new Sprite(spritesets[PIRATE]->sprites[2][5],0);
 spritesets[PIRATE]->sprites[0][6] = new Sprite(spritesets[PIRATE]->sprites[2][6],0);
 spritesets[PIRATE]->sprites[0][7] = new Sprite(spritesets[PIRATE]->sprites[2][7],0);
 
 spritesets[PIRATE]->sprites[3][0] = new Sprite("img/pirate/kippt um e00",11);
 spritesets[PIRATE]->sprites[3][1] = spritesets[PIRATE]->sprites[3][0];
 spritesets[PIRATE]->sprites[3][2] = new Sprite("img/pirate/kippt um n00",11);
 spritesets[PIRATE]->sprites[3][3] = spritesets[PIRATE]->sprites[3][2];
 spritesets[PIRATE]->sprites[3][4] = new Sprite("img/pirate/kippt um w00",11);
 spritesets[PIRATE]->sprites[3][5] = spritesets[PIRATE]->sprites[3][4];
 spritesets[PIRATE]->sprites[3][6] = new Sprite("img/pirate/kippt um s00",11);
 spritesets[PIRATE]->sprites[3][7] = spritesets[PIRATE]->sprites[3][6];
 }
 
void Graphic_Resources::Load_Barbar()
{
 spritesets[BARBAR] = new SpriteSet();
 
 spritesets[BARBAR]->sprites[1][0] = new Sprite("img/barbar/running e00",8);
 spritesets[BARBAR]->sprites[1][1] = new Sprite("img/barbar/running ne00",8);
 spritesets[BARBAR]->sprites[1][2] = new Sprite("img/barbar/running n00",8);
 spritesets[BARBAR]->sprites[1][3] = new Sprite("img/barbar/running nw00",8);
 spritesets[BARBAR]->sprites[1][4] = new Sprite("img/barbar/running w00",8);
 spritesets[BARBAR]->sprites[1][5] = new Sprite("img/barbar/running sw00",8);
 spritesets[BARBAR]->sprites[1][6] = new Sprite("img/barbar/running s00",8);
 spritesets[BARBAR]->sprites[1][7] = new Sprite("img/barbar/running se00",8);
 
 spritesets[BARBAR]->sprites[2][0] = new Sprite("img/barbar/attack e00",11);
 spritesets[BARBAR]->sprites[2][1] = new Sprite("img/barbar/attack ne00",11);
 spritesets[BARBAR]->sprites[2][2] = new Sprite("img/barbar/attack n00",11);
 spritesets[BARBAR]->sprites[2][3] = new Sprite("img/barbar/attack nw00",11);
 spritesets[BARBAR]->sprites[2][4] = new Sprite("img/barbar/attack w00",11);
 spritesets[BARBAR]->sprites[2][5] = new Sprite("img/barbar/attack sw00",11);
 spritesets[BARBAR]->sprites[2][6] = new Sprite("img/barbar/attack s00",11);
 spritesets[BARBAR]->sprites[2][7] = new Sprite("img/barbar/attack se00",11);
 
 spritesets[BARBAR]->sprites[0][0] = new Sprite(spritesets[BARBAR]->sprites[2][0],0);
 spritesets[BARBAR]->sprites[0][1] = new Sprite(spritesets[BARBAR]->sprites[2][1],0);
 spritesets[BARBAR]->sprites[0][2] = new Sprite(spritesets[BARBAR]->sprites[2][2],0);
 spritesets[BARBAR]->sprites[0][3] = new Sprite(spritesets[BARBAR]->sprites[2][3],0);
 spritesets[BARBAR]->sprites[0][4] = new Sprite(spritesets[BARBAR]->sprites[2][4],0);
 spritesets[BARBAR]->sprites[0][5] = new Sprite(spritesets[BARBAR]->sprites[2][5],0);
 spritesets[BARBAR]->sprites[0][6] = new Sprite(spritesets[BARBAR]->sprites[2][6],0);
 spritesets[BARBAR]->sprites[0][7] = new Sprite(spritesets[BARBAR]->sprites[2][7],0);
 
 spritesets[BARBAR]->sprites[3][0] = new Sprite("img/barbar/tipping over e00",11);
 spritesets[BARBAR]->sprites[3][1] = new Sprite("img/barbar/tipping over ne00",11);
 spritesets[BARBAR]->sprites[3][2] = new Sprite("img/barbar/tipping over n00",11);
 spritesets[BARBAR]->sprites[3][3] = new Sprite("img/barbar/tipping over nw00",11);
 spritesets[BARBAR]->sprites[3][4] = new Sprite("img/barbar/tipping over w00",11);
 spritesets[BARBAR]->sprites[3][5] = new Sprite("img/barbar/tipping over sw00",11);
 spritesets[BARBAR]->sprites[3][6] = new Sprite("img/barbar/tipping over s00",11);
 spritesets[BARBAR]->sprites[3][7] = new Sprite("img/barbar/tipping over se00",11);
 }
 
void Graphic_Resources::Load_Archer()
{
 spritesets[ARCHER] = new SpriteSet();

 spritesets[ARCHER]->sprites[1][0] = new Sprite("img/archer/walking e00",8);
 spritesets[ARCHER]->sprites[1][1] = new Sprite("img/archer/walking ne00",8);
 spritesets[ARCHER]->sprites[1][2] = new Sprite("img/archer/walking n00",8);
 spritesets[ARCHER]->sprites[1][3] = new Sprite("img/archer/walking nw00",8);
 spritesets[ARCHER]->sprites[1][4] = new Sprite("img/archer/walking w00",8);
 spritesets[ARCHER]->sprites[1][5] = new Sprite("img/archer/walking sw00",8);
 spritesets[ARCHER]->sprites[1][6] = new Sprite("img/archer/walking s00",8);
 spritesets[ARCHER]->sprites[1][7] = new Sprite("img/archer/walking se00",8);
 
 spritesets[ARCHER]->sprites[2][0] = new Sprite("img/archer/shooting e00",13);
 spritesets[ARCHER]->sprites[2][1] = new Sprite("img/archer/shooting ne00",13);
 spritesets[ARCHER]->sprites[2][2] = new Sprite("img/archer/shooting n00",13);
 spritesets[ARCHER]->sprites[2][3] = new Sprite("img/archer/shooting nw00",13);
 spritesets[ARCHER]->sprites[2][4] = new Sprite("img/archer/shooting w00",13);
 spritesets[ARCHER]->sprites[2][5] = new Sprite("img/archer/shooting sw00",13);
 spritesets[ARCHER]->sprites[2][6] = new Sprite("img/archer/shooting s00",13);
 spritesets[ARCHER]->sprites[2][7] = new Sprite("img/archer/shooting se00",13);
 
 spritesets[ARCHER]->sprites[0][0] = new Sprite(spritesets[ARCHER]->sprites[2][0],0);
 spritesets[ARCHER]->sprites[0][1] = new Sprite(spritesets[ARCHER]->sprites[2][1],0);
 spritesets[ARCHER]->sprites[0][2] = new Sprite(spritesets[ARCHER]->sprites[2][2],0);
 spritesets[ARCHER]->sprites[0][3] = new Sprite(spritesets[ARCHER]->sprites[2][3],0);
 spritesets[ARCHER]->sprites[0][4] = new Sprite(spritesets[ARCHER]->sprites[2][4],0);
 spritesets[ARCHER]->sprites[0][5] = new Sprite(spritesets[ARCHER]->sprites[2][5],0);
 spritesets[ARCHER]->sprites[0][6] = new Sprite(spritesets[ARCHER]->sprites[2][6],0);
 spritesets[ARCHER]->sprites[0][7] = new Sprite(spritesets[ARCHER]->sprites[2][7],0);
 
 spritesets[ARCHER]->sprites[3][0] = new Sprite("img/archer/tipping over e00",13);
 spritesets[ARCHER]->sprites[3][1] = new Sprite("img/archer/tipping over ne00",13);
 spritesets[ARCHER]->sprites[3][2] = new Sprite("img/archer/tipping over n00",13);
 spritesets[ARCHER]->sprites[3][3] = new Sprite("img/archer/tipping over nw00",13);
 spritesets[ARCHER]->sprites[3][4] = new Sprite("img/archer/tipping over w00",13);
 spritesets[ARCHER]->sprites[3][5] = new Sprite("img/archer/tipping over sw00",13);
 spritesets[ARCHER]->sprites[3][6] = new Sprite("img/archer/tipping over s00",13);
 spritesets[ARCHER]->sprites[3][7] = new Sprite("img/archer/tipping over se00",13);
 }

void Graphic_Resources::Load_Viking()
{
 spritesets[VIKING] = new SpriteSet();
 
 spritesets[VIKING]->sprites[0][0] = new Sprite("img/viking/looking e00",13);
 spritesets[VIKING]->sprites[0][1] = new Sprite("img/viking/looking ne00",13);
 spritesets[VIKING]->sprites[0][2] = new Sprite("img/viking/looking n00",13);
 spritesets[VIKING]->sprites[0][3] = new Sprite("img/viking/looking nw00",13);
 spritesets[VIKING]->sprites[0][4] = new Sprite("img/viking/looking w00",13);
 spritesets[VIKING]->sprites[0][5] = new Sprite("img/viking/looking sw00",13);
 spritesets[VIKING]->sprites[0][6] = new Sprite("img/viking/looking s00",13);
 spritesets[VIKING]->sprites[0][7] = new Sprite("img/viking/looking se00",13);

 spritesets[VIKING]->sprites[1][0] = new Sprite("img/viking/running e00",8,64,40);
 spritesets[VIKING]->sprites[1][1] = new Sprite("img/viking/running ne00",8,64,40);
 spritesets[VIKING]->sprites[1][2] = new Sprite("img/viking/running n00",8,64,40);
 spritesets[VIKING]->sprites[1][3] = new Sprite("img/viking/running nw00",8,64,40);
 spritesets[VIKING]->sprites[1][4] = new Sprite("img/viking/running w00",7,64,40);
 spritesets[VIKING]->sprites[1][5] = new Sprite("img/viking/running sw00",8,64,40);
 spritesets[VIKING]->sprites[1][6] = new Sprite("img/viking/running s00",8,64,40);
 spritesets[VIKING]->sprites[1][7] = new Sprite("img/viking/running se00",8,64,40);
 
 spritesets[VIKING]->sprites[2][0] = new Sprite("img/viking/attack e00",13,64,40);
 spritesets[VIKING]->sprites[2][1] = new Sprite("img/viking/attack ne00",13,64,40);
 spritesets[VIKING]->sprites[2][2] = new Sprite("img/viking/attack n00",13,64,40);
 spritesets[VIKING]->sprites[2][3] = new Sprite("img/viking/attack nw00",13,64,40);
 spritesets[VIKING]->sprites[2][4] = new Sprite("img/viking/attack w00",13,64,40);
 spritesets[VIKING]->sprites[2][5] = new Sprite("img/viking/attack sw00",13,64,40);
 spritesets[VIKING]->sprites[2][6] = new Sprite("img/viking/attack s00",13,64,40);
 spritesets[VIKING]->sprites[2][7] = new Sprite("img/viking/attack se00",13,64,40);
 
 spritesets[VIKING]->sprites[3][0] = new Sprite("img/viking/tipping over e00",11,64,40);
 spritesets[VIKING]->sprites[3][1] = new Sprite("img/viking/tipping over ne00",11,64,40);
 spritesets[VIKING]->sprites[3][2] = new Sprite("img/viking/tipping over n00",11,64,40);
 spritesets[VIKING]->sprites[3][3] = new Sprite("img/viking/tipping over nw00",11,64,40);
 spritesets[VIKING]->sprites[3][4] = new Sprite("img/viking/tipping over w00",11,64,40);
 spritesets[VIKING]->sprites[3][5] = new Sprite("img/viking/tipping over sw00",11,64,40);
 spritesets[VIKING]->sprites[3][6] = new Sprite("img/viking/tipping over s00",11,64,40);
 spritesets[VIKING]->sprites[3][7] = new Sprite("img/viking/tipping over se00",11,64,40);
 }
 
void Graphic_Resources::Load_Lava()
{
 spritesets[LAVA] = new SpriteSet();
 
 spritesets[LAVA]->sprites[0][0] = new Sprite("img/lava/talking e00",9);
 spritesets[LAVA]->sprites[0][1] = new Sprite("img/lava/talking ne00",9);
 spritesets[LAVA]->sprites[0][2] = new Sprite("img/lava/talking n00",9);
 spritesets[LAVA]->sprites[0][3] = new Sprite("img/lava/talking nw00",9);
 spritesets[LAVA]->sprites[0][4] = new Sprite("img/lava/talking w00",9);
 spritesets[LAVA]->sprites[0][5] = new Sprite("img/lava/talking sw00",9);
 spritesets[LAVA]->sprites[0][6] = new Sprite("img/lava/talking s00",9);
 spritesets[LAVA]->sprites[0][7] = new Sprite("img/lava/talking se00",9);

 spritesets[LAVA]->sprites[1][0] = new Sprite("img/lava/walking e00",8);
 spritesets[LAVA]->sprites[1][1] = new Sprite("img/lava/walking ne00",8);
 spritesets[LAVA]->sprites[1][2] = new Sprite("img/lava/walking n00",8);
 spritesets[LAVA]->sprites[1][3] = new Sprite("img/lava/walking nw00",8);
 spritesets[LAVA]->sprites[1][4] = new Sprite("img/lava/walking w00",8);
 spritesets[LAVA]->sprites[1][5] = new Sprite("img/lava/walking sw00",8);
 spritesets[LAVA]->sprites[1][6] = new Sprite("img/lava/walking s00",8);
 spritesets[LAVA]->sprites[1][7] = new Sprite("img/lava/walking se00",8);
 
 spritesets[LAVA]->sprites[2][0] = new Sprite("img/lava/attack e00",13);
 spritesets[LAVA]->sprites[2][1] = new Sprite("img/lava/attack ne00",13);
 spritesets[LAVA]->sprites[2][2] = new Sprite("img/lava/attack n00",13);
 spritesets[LAVA]->sprites[2][3] = new Sprite("img/lava/attack nw00",13);
 spritesets[LAVA]->sprites[2][4] = new Sprite("img/lava/attack w00",13);
 spritesets[LAVA]->sprites[2][5] = new Sprite("img/lava/attack sw00",13);
 spritesets[LAVA]->sprites[2][6] = new Sprite("img/lava/attack s00",13);
 spritesets[LAVA]->sprites[2][7] = new Sprite("img/lava/attack se00",13);
 
 spritesets[LAVA]->sprites[3][0] = new Sprite("img/lava/disintegrate e00",17);
 spritesets[LAVA]->sprites[3][1] = new Sprite("img/lava/disintegrate ne00",17);
 spritesets[LAVA]->sprites[3][2] = new Sprite("img/lava/disintegrate n00",17);
 spritesets[LAVA]->sprites[3][3] = new Sprite("img/lava/disintegrate nw00",17);
 spritesets[LAVA]->sprites[3][4] = new Sprite("img/lava/disintegrate w00",17);
 spritesets[LAVA]->sprites[3][5] = new Sprite("img/lava/disintegrate sw00",17);
 spritesets[LAVA]->sprites[3][6] = new Sprite("img/lava/disintegrate s00",17);
 spritesets[LAVA]->sprites[3][7] = new Sprite("img/lava/disintegrate se00",17);
 }
 
void Graphic_Resources::Load_Knight()
{
 spritesets[KNIGHT] = new SpriteSet();
 
 spritesets[KNIGHT]->sprites[0][0] = new Sprite("img/knight/greeting e00",9);
 spritesets[KNIGHT]->sprites[0][1] = new Sprite("img/knight/greeting ne00",9);
 spritesets[KNIGHT]->sprites[0][2] = new Sprite("img/knight/greeting n00",9);
 spritesets[KNIGHT]->sprites[0][3] = new Sprite("img/knight/greeting nw00",9);
 spritesets[KNIGHT]->sprites[0][4] = new Sprite("img/knight/greeting w00",9);
 spritesets[KNIGHT]->sprites[0][5] = new Sprite("img/knight/greeting sw00",9);
 spritesets[KNIGHT]->sprites[0][6] = new Sprite("img/knight/greeting s00",9);
 spritesets[KNIGHT]->sprites[0][7] = new Sprite("img/knight/greeting se00",9);

 spritesets[KNIGHT]->sprites[1][0] = new Sprite("img/knight/walking e00",8);
 spritesets[KNIGHT]->sprites[1][1] = new Sprite("img/knight/walking ne00",8);
 spritesets[KNIGHT]->sprites[1][2] = new Sprite("img/knight/walking n00",8);
 spritesets[KNIGHT]->sprites[1][3] = new Sprite("img/knight/walking nw00",8);
 spritesets[KNIGHT]->sprites[1][4] = new Sprite("img/knight/walking w00",8);
 spritesets[KNIGHT]->sprites[1][5] = new Sprite("img/knight/walking sw00",8);
 spritesets[KNIGHT]->sprites[1][6] = new Sprite("img/knight/walking s00",8);
 spritesets[KNIGHT]->sprites[1][7] = new Sprite("img/knight/walking se00",8);
 
 spritesets[KNIGHT]->sprites[2][0] = new Sprite("img/knight/attack e00",13);
 spritesets[KNIGHT]->sprites[2][1] = new Sprite("img/knight/attack ne00",13);
 spritesets[KNIGHT]->sprites[2][2] = new Sprite("img/knight/attack n00",13);
 spritesets[KNIGHT]->sprites[2][3] = new Sprite("img/knight/attack nw00",13);
 spritesets[KNIGHT]->sprites[2][4] = new Sprite("img/knight/attack w00",13);
 spritesets[KNIGHT]->sprites[2][5] = new Sprite("img/knight/attack sw00",13);
 spritesets[KNIGHT]->sprites[2][6] = new Sprite("img/knight/attack s00",13);
 spritesets[KNIGHT]->sprites[2][7] = new Sprite("img/knight/attack se00",13);
 
 spritesets[KNIGHT]->sprites[3][0] = new Sprite("img/knight/tipping over e00",9);
 spritesets[KNIGHT]->sprites[3][1] = new Sprite("img/knight/tipping over ne00",9);
 spritesets[KNIGHT]->sprites[3][2] = new Sprite("img/knight/tipping over n00",9);
 spritesets[KNIGHT]->sprites[3][3] = new Sprite("img/knight/tipping over nw00",9);
 spritesets[KNIGHT]->sprites[3][4] = new Sprite("img/knight/tipping over w00",9);
 spritesets[KNIGHT]->sprites[3][5] = new Sprite("img/knight/tipping over sw00",9);
 spritesets[KNIGHT]->sprites[3][6] = new Sprite("img/knight/tipping over s00",9);
 spritesets[KNIGHT]->sprites[3][7] = new Sprite("img/knight/tipping over se00",9);
 }
 
void Graphic_Resources::Load_Dwarf()
{
 spritesets[DWARF] = new SpriteSet();
 
 spritesets[DWARF]->sprites[0][0] = new Sprite("img/dwarf/talking e00",9);
 spritesets[DWARF]->sprites[0][1] = new Sprite("img/dwarf/talking ne00",9);
 spritesets[DWARF]->sprites[0][2] = new Sprite("img/dwarf/talking n00",9);
 spritesets[DWARF]->sprites[0][3] = new Sprite("img/dwarf/talking nw00",9);
 spritesets[DWARF]->sprites[0][4] = new Sprite("img/dwarf/talking w00",9);
 spritesets[DWARF]->sprites[0][5] = new Sprite("img/dwarf/talking sw00",9);
 spritesets[DWARF]->sprites[0][6] = new Sprite("img/dwarf/talking s00",9);
 spritesets[DWARF]->sprites[0][7] = new Sprite("img/dwarf/talking se00",9);

 spritesets[DWARF]->sprites[1][0] = new Sprite("img/dwarf/walking e00",8);
 spritesets[DWARF]->sprites[1][1] = new Sprite("img/dwarf/walking ne00",8);
 spritesets[DWARF]->sprites[1][2] = new Sprite("img/dwarf/walking n00",8);
 spritesets[DWARF]->sprites[1][3] = new Sprite("img/dwarf/walking nw00",8);
 spritesets[DWARF]->sprites[1][4] = new Sprite("img/dwarf/walking w00",8);
 spritesets[DWARF]->sprites[1][5] = new Sprite("img/dwarf/walking sw00",8);
 spritesets[DWARF]->sprites[1][6] = new Sprite("img/dwarf/walking s00",8);
 spritesets[DWARF]->sprites[1][7] = new Sprite("img/dwarf/walking se00",8);
 
 spritesets[DWARF]->sprites[2][0] = new Sprite("img/dwarf/attack e00",13,64,40);
 spritesets[DWARF]->sprites[2][1] = new Sprite("img/dwarf/attack ne00",13,64,40);
 spritesets[DWARF]->sprites[2][2] = new Sprite("img/dwarf/attack n00",13,64,40);
 spritesets[DWARF]->sprites[2][3] = new Sprite("img/dwarf/attack nw00",13,64,40);
 spritesets[DWARF]->sprites[2][4] = new Sprite("img/dwarf/attack w00",13,64,40);
 spritesets[DWARF]->sprites[2][5] = new Sprite("img/dwarf/attack sw00",13,64,40);
 spritesets[DWARF]->sprites[2][6] = new Sprite("img/dwarf/attack s00",13,64,40);
 spritesets[DWARF]->sprites[2][7] = new Sprite("img/dwarf/attack se00",13,64,40);
 
 spritesets[DWARF]->sprites[3][0] = new Sprite("img/dwarf/tipping over e00",11);
 spritesets[DWARF]->sprites[3][1] = new Sprite("img/dwarf/tipping over ne00",11);
 spritesets[DWARF]->sprites[3][2] = new Sprite("img/dwarf/tipping over n00",11);
 spritesets[DWARF]->sprites[3][3] = new Sprite("img/dwarf/tipping over nw00",11);
 spritesets[DWARF]->sprites[3][4] = new Sprite("img/dwarf/tipping over w00",11);
 spritesets[DWARF]->sprites[3][5] = new Sprite("img/dwarf/tipping over sw00",11);
 spritesets[DWARF]->sprites[3][6] = new Sprite("img/dwarf/tipping over s00",11);
 spritesets[DWARF]->sprites[3][7] = new Sprite("img/dwarf/tipping over se00",11);
 }
 
void Graphic_Resources::Load_Textures()
{
 textures[GRASS] = LoadTexture("img/back/grass.bmp");
 textures[STONE] = LoadTexture("img/back/stone.bmp");
 textures[MENU]=LoadTexture("img/menu/menu1.bmp");
 textures[OKBUTTON]=LoadTexture("img/menu/okbutton.bmp");
 textures[TITLE]= LoadTexture("img/menu/title.bmp");
 sprites[ARROW]=new Sprite("img/arrow/",32,16,18);
 sprites[TREE1]=new Sprite("img/obs/tree_1",1,66,32);
 sprites[ROCK1]=new Sprite("img/obs/rock_1",1,32,26);
 }
 
