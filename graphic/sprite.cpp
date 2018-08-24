#include <GL/gl.h>
#include <stdio.h>
#include "sprite.h"

//------------------------------------------------------------------------------
typedef unsigned char Byte;

//------------------------------------------------------------------------------
Sprite::Sprite(const char* name, int cnt, int xof, int yof)
{ 
 char ch[1024];  
 int width, height;                                    
 images = new GLuint[cnt];                 
 for (int i(0); i<cnt; i++)
 {
  if (i<10)
  sprintf(ch,"%s0%d.bmp",name,i);
  else       
  sprintf(ch,"%s%d.bmp",name,i);    
  images[i]=LoadTexture(ch);   
  }
  image_number = cnt;
  
  glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&height);
  
  if (xof == -1)  
  {
   x2 = width/2;
   x1 = -x2;
   y2 = 3*height/4;
   y1 = y2-height;
   }
   else
   { 
    x1 = -xof ;
    x2 = width - xof;
    y1 = -yof;
    y2 = height - yof; 
    }         	
}
//------------------------------------------------------------------------------

Sprite::Sprite(Sprite* spr, int ind)
{                                  
 images = &(spr->images[ind]);
 image_number = 1.0f;
 x1 = spr->x1;
 x2 = spr->x2;
 y1 = spr->y1;
 y2 = spr->y2;        	
}
//------------------------------------------------------------------------------

GLuint Sprite::LoadTexture(const char * filename)
{
    GLuint texture;
    int width, height, size;
    Byte * data, *rgba;
    FILE * file;
    
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    
    fseek(file,18,SEEK_SET);
    fread(&width, sizeof(int),1,file);
    fread(&height, sizeof(int),1,file);
    size = width * height * 3;
    fseek(file,28,SEEK_CUR);
    data = new Byte[size];
    fread( data,size, 1, file );
    fclose( file );

    rgba = new Byte[width * height * 4];  
	for( int i(0), ia(0); i < size; i += 3, ia +=4 )
	{
        rgba[ia] = data[i+2];
        rgba[ia+1] = data[i+1];
        rgba[ia+2] = data[i];
        if ( (data[i]==data[0]) && (data[i+1]==data[1]) && (data[i+2]==data[2]) )
        rgba[ia+3] = 0;
        else
        rgba[ia+3] = 255;      
	}
	delete[] data;
	
    glGenTextures( 1, &texture ); 
    glBindTexture( GL_TEXTURE_2D, texture ); 
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); 
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexImage2D( GL_TEXTURE_2D,0, GL_RGBA, width, height,0, GL_RGBA, GL_UNSIGNED_BYTE, rgba );
    delete[] rgba;
    return texture; 
}
//------------------------------------------------------------------------------

Sprite::~Sprite()
{
 for (int i(0);i < image_number; i++)
 glDeleteTextures( 1, &(images[0]));               
 }
//------------------------------------------------------------------------------ 

SpriteSet::~SpriteSet()
{
 for (int i = 0; i < 4; i++)
 for (int j = 0; j < 8; j++)
 delete sprites[i][j];                      
 }
