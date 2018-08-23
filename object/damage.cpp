#include "damage.h"
#include "game.h"

Damage_Report::Damage_Report(float setx, float sety)
{
 x = setx;
 y = sety;
 life = 50;
 }

Damage_Report::~Damage_Report()
{
 delete [] str;
 }                               

void Damage_Report::Step()
{
 y += life*0.05;
 if (life > 0)
 life--;
 else
 Game::Remove(this) ;   
 } 
 
void Damage_Report::Draw()
{
 glColor3f(1.0f,0.0f,0.0f);
 glRasterPos2f(x-10.0f,y+8.0f);
 glutBitmapString( GLUT_BITMAP_9_BY_15, (const unsigned char*)str );
 glColor3f(1.0f,1.0f,1.0f); 
 } 
