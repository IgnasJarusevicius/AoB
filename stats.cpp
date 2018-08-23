#include "stats.h"
#include "graphic/graphics.h"
#include "stdio.h"
#include <GL/freeglut.h>

int Stats::score;
int Stats::multi;
int Stats::level;
int Stats::unlocked; 
int Stats::stats[2];
int Stats::xp[2];
int Stats::xp2[2];

void Stats::Init()
{
 score = 0;
 multi = 3;
 level = 0; 
 unlocked = 0x0007;
 stats[0] = 1; 
 xp[0] = 0;
 xp2[0] = 250;
 stats[1] = 1; 
 xp[1] = 0;
 xp2[1] = 250;
   
 }
 
void Stats::Damage(int dmg, bool rng)
{
 score += multi*dmg; 
 if (rng)
 Add(1,dmg);
 else 
 Add(0,dmg);
 }

void Stats::EndTurn()
{
 multi -= multi > 1 ? 1:0;    
 }
 
void Stats::Die()
{
 multi += multi < 10 ? 1:0;   
 }

void Stats::Add(int i,int val)
{
 if (stats[i] == 5)
 return;
 
 xp[i] += val;
 if (xp[i] >= xp2[i])
 {
  if (stats[i] != 4) 
  {
   xp[i] -= xp2[i];
   xp2[i] = 200*stats[i]*stats[i]; 
   } 
   else
   xp[i] = xp2[i]; 
   stats[i] += 1;  
   Unlock();       
  }   
 }
 
void Stats::Draw(float x, float y)
{
 char* str = new char[20];     
 glColor3f(0.8f,0.25f,0.2f); 
 if (xp[0] >0)
 Draw_Rectangle(x+10.0f,x+10.0f+120*xp[0]/xp2[0],y-110.0f,y-100.0f);
 glRasterPos3f(x+10.0f,y-95.0f,200.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)"Melee");
 glRasterPos3f(x+135.0f,y-109.0f,200.0f);
 sprintf(str,"Lv: %d",stats[0]); 
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str);  
 glColor3f(0.2f,0.8f,0.15f);  
 if (xp[1] >0)
 Draw_Rectangle(x+10.0f,x+10.0f+120*xp[1]/xp2[1],y-140.0f,y-130.0f); 
 glRasterPos3f(x+10.0f,y-125.0f,200.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)"Ranged");
 glRasterPos3f(x+135.0f,y-139.0f,200.0f);
 sprintf(str,"Lv: %d",stats[1]);
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str);   
 glColor3f(1.0f,1.0f,1.0f);
 Draw_Rectangle_Outline(x,x+180.0f,y,y-160.0f,200.0f);
 Draw_Rectangle_Outline(x+10.0f,x+130.0f,y-110.0f,y-100.0f,200.0f); 
 Draw_Rectangle_Outline(x+10.0f,x+130.0f,y-140.0f,y-130.0f,200.0f); 
 glColor3f(0.2f,0.8f,0.8f);   
 
 glRasterPos3f(x+50.0f,y-20.0f,200.0f);
 sprintf(str,"Battle: %d",level); 
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)str);
 glColor3f(0.8f,0.8f,0.2f);  
 glRasterPos3f(x+20.0f,y-50.0f,200.0f);
 sprintf(str,"Score: %d",score); 
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)str);
 glRasterPos3f(x+60.0f,y-65.0f,200.0f); 
 sprintf(str,"x%d",multi); 
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str);        
 }

void Stats::Unlock()
{
 if (stats[0]>= 3)
 unlocked |= 0x0008;
 if (stats[0]>= 2 && stats[1]>= 2)
 unlocked |= 0x0010; 
 if (stats[1]>= 3)
 unlocked |= 0x0020; 
 if (stats[0]>= 4)
 unlocked |= 0x0040; 
 if (stats[0]>= 3 && stats[1]>=2)
 unlocked |= 0x0080; 
 if (stats[1]>= 4)
 unlocked |= 0x0100;
 if (stats[0]>= 5)
 unlocked |= 0x0200;
 if (stats[0]== 4 && stats[1]>=3)
 unlocked |= 0x0400; 
 }
 
 
 
 


