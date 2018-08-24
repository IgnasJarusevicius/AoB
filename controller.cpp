#include "game.h"
#include "audio.h"
#include "controller.h"
#include <math.h>
#include <stdio.h>
#define POINTS 8

//------------------------------------------------------------------------------
extern Controller* game;

//------------------------------------------------------------------------------
Menu::Menu(Controller* c)
{
 active_game = c;                      
 }

Menu::~Menu()
{
 if (active_game)
 delete active_game;            
 }

//------------------------------------------------------------------------------
void Menu::Display() 
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity(); 
 glEnable( GL_TEXTURE_2D );
 
 Draw_Texture(Graphic_Resources::textures[TITLE],326.0f,710.0f,600.0f,664.0f,0.0f);
 
 glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[MENU]);
 int i;
 float y1, y2;
 if (active_game == NULL) {
    y1 = 0.2f;
    y2 = 274.0f;
    i = 1;  
    }
    else{
         y1 = 0.0f;
         y2 = 180.0f;
         i = 0; 
         }  
 glBegin (GL_QUADS);
 for (; i < 5; i++)
 {
  if (Mouse::Position(416.0f,608.0f,y2,y2+64.0))
  {
   glColor3f(1.0f,1.0f,0.0f);
   if (Mouse::Button(LEFT_UP))
   {
    Audio::Play(PLAY_CLICK);
    switch (i)
    {
     case 0: ((Game*)active_game)->Resume_Game();break;
     case 1: exit(0);
     case 2: new Credits(active_game);break;
     case 3: new How_To(active_game);break;
     case 4: delete active_game; new Game_Start();break;                   
     }
    } 
   } 
   else glColor3f(1.0f,1.0f,1.0f); 
    
  glTexCoord2d(0.0f,y1);glVertex3f(416.0f,y2,0.0f);
  glTexCoord2d(1.0f,y1);glVertex3f(608.0f,y2,0.0f);
  y1 += 0.2f;
  y2 += 64.0f;   
  glTexCoord2d(1.0f,y1);glVertex3f(608.0f,y2,0.0f);
  glTexCoord2d(0.0f,y1);glVertex3f(416.0f,y2,0.0f);
  }
 glEnd();
 }

//------------------------------------------------------------------------------ 
Game_Start::Game_Start()
{
 if (game)
 delete game;
 game = this;  
 Stats::Init();
 points = POINTS;
 back = true;
 characters[0] = new Orc(0,0);
 characters[1] = new Pirate(0,0);
 characters[2] = new Hunter(0,0);
 characters[3] = new Barbar(0,0); 
 characters[4] = new Skel_War(0,0);
 characters[5] = new Skel_Arch(0,0);
 characters[6] = new Viking(0,0);
 characters[7] = new Lava(0,0);
 characters[8] = new Archer(0,0);
 characters[9] = new Knight(0,0); 
 characters[10] = new Dwarf(0,0); 
 team = new int[8];
 for (int i = 0; i < 8; i++)
 team[i] = -1;
 }
 
//------------------------------------------------------------------------------ 
Game_Start::Game_Start(int a)
{
 team = Game::team;
 Game::team = NULL;                         
 if (game)
 delete game;
 game = this;
 back = false;
 characters[0] = new Orc(0,0);
 characters[1] = new Pirate(0,0);
 characters[2] = new Hunter(0,0);
 characters[3] = new Barbar(0,0); 
 characters[4] = new Skel_War(0,0);
 characters[5] = new Skel_Arch(0,0);
 characters[6] = new Viking(0,0);
 characters[7] = new Lava(0,0);
 characters[8] = new Archer(0,0);
 characters[9] = new Knight(0,0); 
 characters[10] = new Dwarf(0,0); 
 points = POINTS;
 points += (int) (floor((-1.0+sqrt(1.0+Stats::score/62.5))/2.0)); 
 for (int i = 0; i < 8; i++)
 if (team[i] != -1)
 points -= 1+team[i]/3;
 }

//------------------------------------------------------------------------------ 
Game_Start::~Game_Start()
{
 for (int i = 0; i<11;i++)
 delete characters[i]; 
 }

//------------------------------------------------------------------------------
void Game_Start::Display() 
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity(); 
 glEnable( GL_TEXTURE_2D );

 float x1 = 272;
 float y1 = 300;
 
 for (int i =0; i<11; i++)
 {
  if (Stats::unlocked&(0x0001<<i))
  Draw_Texture(characters[i]->spriteset->sprites[0][6]->images[0],x1,x1+96,y1,y1+96,0);
  y1 += 128;
  if (i%3 ==2){
     y1 = 300;
     x1 += 128;       
     }         
  }
   
  x1 = 128;
  y1 = 96;  
  for (int i =0; i<8; i++) 
  {
   if (team[i] != -1)
   Draw_Texture(characters[team[i]]->spriteset->sprites[0][6]->images[0],x1,x1+96,y1,y1+96,0); 
   x1 += 96;      
   }
 
 if (back) 
 {
  if (Mouse::Position(22,150,28,76))
  {
   glColor3f(1.0f,1.0f,0.0f); 
   if (Mouse::Button(LEFT_UP)){
      Audio::Play(PLAY_CLICK);
      game = new Menu(NULL);
      delete team;
      delete this;
      }              
   }
   else glColor3f(1.0f,1.0f,1.0f);
  glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[MENU]);  
  glBegin (GL_QUADS);
  glTexCoord2d(1.0,0.2);glVertex3f(150,76,0);
  glTexCoord2d(0.0,0.2);glVertex3f(22,76,0);
  glTexCoord2d(0.0,0.0);glVertex3f(22,28,0);
  glTexCoord2d(1.0,0.0);glVertex3f(150,28,0);
  glEnd();     
  } 
 
 if (points != POINTS)  
 {
  if (Mouse::Position(920,968,28,70))
  {
   glColor3f(1.0f,1.0f,0.0f); 
   if(Mouse::Button(LEFT_UP))
    {
    Audio::Play(PLAY_CLICK);                        
    game = new Game(team);
    delete this;
    }             
   }
   else glColor3f(1.0f,1.0f,1.0f);  
  Draw_Texture(Graphic_Resources::textures[OKBUTTON],920.0f,968.0f,28.0f,76.0f,0.0f);
  }
   
 glDisable( GL_TEXTURE_2D );
  
 x1 = 256;
 y1 = 284;
 for (int i =0; i<11; i++)
 { 
  if (Mouse::Position(x1,x1+127,y1,y1+127))
  {
   if (Stats::unlocked&(1<<i)) 
      {                                         
       Display_Info(i); 
       if (Mouse::Button(LEFT_UP))
          for (int j = 0; j < 8; j++)    
          if ((team[j] == -1)&&(points >= 1+i/3))  
             {
              team[j] = i;
              points -= 1+i/3;
              Audio::Play(PLAY_CLICK);
              break;            
              } 
       }else Unlock_Info(i);
   glColor3f(0.0f,1.0f,0.0f);                   
   }
  else
  glColor3f(1.0f,0.0f,0.0f);  
  Draw_Rectangle_Outline(x1,x1+127,y1,y1+127,0);
  y1 += 128;
  if (i%3 ==2)
  {
   y1 = 284;
   x1 += 128;       
   }         
  } 
 
 x1 = 128;
 y1 = 96;
 for (int i =0; i<8; i++)
 {
  if (Mouse::Position(x1,x1+95,y1,y1+95)){
     glColor3f(0.0f,1.0f,0.0f); 
     if (team[i] != -1){
        Display_Info(team[i]);
        if (Mouse::Button(LEFT_UP)){
           points += 1+team[i]/3;
           team[i] = -1;  
           Audio::Play(PLAY_CLICK);
           }
        }               
     }
     else
     glColor3f(1.0f,1.0f,1.0f);  
     Draw_Rectangle_Outline(x1,x1+95,y1,y1+95,0); 
     x1 += 96;      
   }
  
  char* str = new char[20]; 
  glColor3f(0.8f,0.8f,0.2f);  
  glRasterPos3f(64.0f,560.0f,200.0f);
  sprintf(str,"Score: %d",Stats::score); 
  glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)str);
  glRasterPos3f(64.0f,520.0f,200.0f);
  sprintf(str,"Melee lv.:  %d",Stats::stats[0]); 
  glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str); 
  glRasterPos3f(64.0f,500.0f,200.0f);
  sprintf(str,"Ranged lv.: %d",Stats::stats[1]); 
  glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str);  
  glColor3f(1.0f,1.0f,1.0f); 
  glRasterPos3f(64.0f,600.0f,200.0f);
  sprintf(str,"Battle: %d",Stats::level+1); 
  glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)str);
  glRasterPos3f(780,60,0);
  sprintf(str,"Points: %d",points); 
  glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)str);  
 }
 
//------------------------------------------------------------------------------ 
void Game_Start::Display_Info(int ind)
{
 glColor3f(0.5f,1.0f,0.2f);   
 char* str = new char[18]; 
 glRasterPos3f(240,240,0);
 sprintf(str,"HP: %d",characters[ind]->maxhp); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str); 
 glRasterPos3f(400,240,0);
 sprintf(str,"Damage: %d - %d",characters[ind]->dmg,characters[ind]->dmg+characters[ind]->dmg2); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str); 
 glRasterPos3f(625,240,0);
 sprintf(str,"Defense: %d / %d",characters[ind]->def,characters[ind]->def2); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str);
 glColor3f(0.8f,0.8f,0.2f);  
 glRasterPos3f(640,214,0);
 sprintf(str,"Req. points : %d",1+ind/3); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str);  
 Draw_Rectangle_Outline(210,800,230,260,0);
  
 delete[] str;
 }

//------------------------------------------------------------------------------ 
void Game_Start::Unlock_Info(int ind)
{
 int a,b;
 switch (ind)
 {
  case 3: a = 3 ; b = 1 ; break;
  case 4: a = 2 ; b = 3 ; break;
  case 5: a = 2 ; b = 2 ; break;
  case 6: a = 4 ; b = 1 ; break;
  case 7: a = 3 ; b = 2 ; break;
  case 8: a = 1 ; b = 4 ; break;
  case 9: a = 4 ; b = 3 ; break;
  case 10: a = 5 ; b = 1 ; break;
  default: return;
  }              
 char* str = new char[20]; 
 glColor3f(0.5f,1.0f,0.2f); 
 glRasterPos3f(240,240,0);
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)"LOCKED"); 
 glRasterPos3f(400,240,0);
 sprintf(str,"Req. Melee lv.: %d",a); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str); 
 glRasterPos3f(625,240,0);
 sprintf(str,"Req. Ranged lv.: %d",b); 
 glutBitmapString(GLUT_BITMAP_9_BY_15,(const unsigned char*)str);
 glColor3f(0.8f,0.8f,0.2f);  
 Draw_Rectangle_Outline(210,800,230,260,0); 
 delete[] str;
 }
 
//------------------------------------------------------------------------------ 
void Loading::Display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity();     
 glColor3f(0.8f,0.8f,0.2f);      
 glRasterPos3f(450,400,0);
 glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)"LOADING...");      
 glutSwapBuffers();
 Graphic_Resources::Load_Graphics();
 Audio::Init();
 game = new Menu(NULL);
 delete this;      
 }
//------------------------------------------------------------------------------ 
Game_Over::Game_Over()
{
 delete game;
 game = this;                     
 }
 
//------------------------------------------------------------------------------ 
void Game_Over::Display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity();     
 glColor3f(0.8f,0.8f,0.2f);      
 glRasterPos3f(450.0f,400.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)"GAME OVER");      
 
 if (Mouse::Button(ANY_UP))
 {
  game = new Menu(NULL);
  delete this;
  }      
 }

//------------------------------------------------------------------------------ 
void Level::Display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity();     
 glColor3f(0.8f,0.8f,0.2f); 
 char* str = new char[16]; 
 sprintf(str,"Battle: %d",Stats::level);      
 glRasterPos3f(450.0f,400.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,(const unsigned char*)str);      
 
 if (Mouse::Button(ANY_UP))
 ((Game*)active_game)->Resume_Game();      
 }

//------------------------------------------------------------------------------ 
Level::Level(Controller* c)
{
 active_game = c;                      
 }
 
//------------------------------------------------------------------------------
How_To::How_To(Controller* c)
{
 active_game = c;
 delete game;
 game = this;                          
 }
 
//------------------------------------------------------------------------------
void How_To::Display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity(); 
 glEnable( GL_TEXTURE_2D );
 glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[MENU]);  
 if (Mouse::Position(22,150,28,76))
 {
  glColor3f(1.0f,1.0f,0.0f);
  if (Mouse::Button(LEFT_UP))
  Return();                                
  }
  else glColor3f(1.0f,1.0f,1.0f); 
 glBegin (GL_QUADS);
 glTexCoord2d(1.0f,0.2f);glVertex3f(150.0f,76.0f,0.0f);
 glTexCoord2d(0.0f,0.2f);glVertex3f(22.0f,76.0f,0.0f);
 glTexCoord2d(0.0f,0.0f);glVertex3f(22.0f,28.0f,0.0f);
 glTexCoord2d(1.0f,0.0f);glVertex3f(150.0f,28.0f,0.0f);
 glColor3f(1.0f,1.0f,1.0f);  
 glTexCoord2d(1.0f,0.8f);glVertex3f(622.0f,694.0f,0.0f);
 glTexCoord2d(0.0f,0.8f);glVertex3f(430.0f,694.0f,0.0f);
 glTexCoord2d(0.0f,0.6f);glVertex3f(430.0f,630.0f,0.0f);
 glTexCoord2d(1.0f,0.6f);glVertex3f(622.0f,630.0f,0.0f);
 glEnd();  
 glDisable( GL_TEXTURE_2D );
 glColor3f(0.1f,0.8f,0.8f);     
 glRasterPos3f(360.0f,550.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Mouse Left Button");
 glRasterPos3f(360.0f,500.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Mouse Right Button");    
 glRasterPos3f(360.0f,450.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"SPACE");    
 glRasterPos3f(360.0f,400.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"ESC");  
 glRasterPos3f(580.0f,550.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Select"); 
 glRasterPos3f(580.0f,500.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Move / Attack");  
 glRasterPos3f(580.0f,450.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"End Turn");  
 glRasterPos3f(580.0f,400.0f,0.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"Menu");              
 } 

//------------------------------------------------------------------------------
void How_To::Return()
{
 Audio::Play(PLAY_CLICK);
 game = new Menu(active_game);                              
 delete this; 
 } 
//------------------------------------------------------------------------------
void Credits::Display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity(); 
 glEnable( GL_TEXTURE_2D );
 glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[MENU]);  
 if (Mouse::Position(22,150,28,76))
 {
  glColor3f(1.0f,1.0f,0.0f);
  if (Mouse::Button(LEFT_UP))
  Return();                                 
  }
  else glColor3f(1.0f,1.0f,1.0f); 
 glBegin (GL_QUADS);
 glTexCoord2d(1.0f,0.2f);glVertex3f(150.0f,76.0f,0.0f);
 glTexCoord2d(0.0f,0.2f);glVertex3f(22.0f,76.0f,0.0f);
 glTexCoord2d(0.0f,0.0f);glVertex3f(22.0f,28.0f,0.0f);
 glTexCoord2d(1.0f,0.0f);glVertex3f(150.0f,28.0f,0.0f);
 glColor3f(1.0f,1.0f,1.0f);  
 glTexCoord2d(1.0f,0.6f);glVertex3f(622.0f,694.0f,0.0f);
 glTexCoord2d(0.0f,0.6f);glVertex3f(430.0f,694.0f,0.0f);
 glTexCoord2d(0.0f,0.4f);glVertex3f(430.0f,630.0f,0.0f);
 glTexCoord2d(1.0f,0.4f);glVertex3f(622.0f,630.0f,0.0f);
 glEnd();                
 } 

//------------------------------------------------------------------------------


