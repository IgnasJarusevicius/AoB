//------------------------------------------------------------------------------
#include "game.h"
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>
#include "object/object.h"
#include "audio.h"
//------------------------------------------------------------------------------
extern Controller* game;

//------------------------------------------------------------------------------
Game::Game(int* ar)
{
 team = ar;
 srand(glutGet(GLUT_ELAPSED_TIME)); //init rand
 Init(); 
 }

//------------------------------------------------------------------------------    
Game::~Game()
{
 //delete all Game_Object
 Game_Object* current, *next;
 current = first;
 while(current != NULL)
 {
  next = current->next;             
  delete current;
  current = next;     
  } 
 //delete other stuff  
 delete ai; 
 delete[] team; 
 }

//------------------------------------------------------------------------------
int Game::enemy_number = 0;
int Game::action_zone[H_SLOT_NUMBER][V_SLOT_NUMBER];  
Game_Object* Game::grid[H_SLOT_NUMBER][V_SLOT_NUMBER]; 
bool Game::active_control = true;
bool Game::turn = true; 
int* Game::team = NULL;  
Game_Object* Game::first = NULL;  
Character* Game::target = NULL;   
Character* Game::active = NULL;

//------------------------------------------------------------------------------    
void Game::Resume_Game()
{
 delete game;
 game = this;       
 }
    
void Game::Init()
{   
   //delete all Game_Object   
   Game_Object* obj, *next;
   obj = first;
   while(obj != NULL)
   {
    next = obj->next;             
    delete obj;
    obj = next;     
    }     
   //reset variables 
   active_control = true;
   turn = true;  
   first = NULL;  
   target = NULL;   
   active = NULL; 
   enemy_number = 0; 
  
   Stats::level++;
   //create player team
   for (int i = 0; i< H_SLOT_NUMBER;i++)
   for (int j = 0; j< V_SLOT_NUMBER;j++)
   {
    grid[i][j] = NULL;
    action_zone[i][j] = 0;   
    }   
    for (int i = 0; i<8; i++)
    if (team[i] != -1)
    {
     obj = Create(team[i],i*2,0,1);   
     obj->player = 1;
     ((Character*)obj)->direction = 2;
     }
    //create enemy team
    int ind = 4+Stats::level; 
    int min = Stats::level/9;
    int max = ind/5;
    int temp;  
    for (int i = 0; i< 8 ;i++ )
    {
     temp = rand()%max;
     if (temp < min)
     temp = min;
     if (temp > 3)
     temp = 3;
     if (temp > ind-1)
     temp = ind-1;
     if (i == 7 && temp < ind-1)
     temp = ind > 4 ? 3 : ind-1;    
     obj = Create(temp*3+rand()%3,i*2,13,1); 
     obj->player = 2;
     ((Character*)obj)->direction = 6;
     ind -= temp+1;   
     enemy_number++;
     if (ind == 0)
     break;
     }
    //create some obstacles
    temp = rand()%10;
    for (int i = 0; i < temp ; i++)
    Create(23,1+rand()%(H_SLOT_NUMBER-2),1+rand()%(V_SLOT_NUMBER-2),1);    
    temp = rand()%10;
    for (int i = 0; i < temp ; i++)
    Create(22,1+rand()%(H_SLOT_NUMBER-2),1+rand()%(V_SLOT_NUMBER-2),1);   
    //show level screen    
    game = new Level(this);
    }
//------------------------------------------------------------------------------    
 
void Game::Key(unsigned char key, int x, int y)
{
    switch (key) 
    {
     case 27 :game = new Menu(this);break;
     case ' ':EndTurn();
              break;
    }
}

//------------------------------------------------------------------------------
Game_Object* Game::Create(int type,float setx,float sety)
{ 
 Game_Object* obj;
 switch (type)
 {
  case 0: obj = new Orc(setx,sety);break;
  case 1: obj = new Pirate(setx,sety);break; 
  case 2: obj = new Hunter(setx,sety);break;
  case 3: obj = new Barbar(setx,sety);break;  
  case 4: obj = new Skel_War(setx,sety);break; 
  case 5: obj = new Skel_Arch(setx,sety);break;
  case 6: obj = new Viking(setx,sety);break;
  case 7: obj = new Lava(setx,sety);break;
  case 8: obj = new Archer(setx,sety);break;
  case 9: obj = new Knight(setx,sety);break;
  case 10: obj = new Dwarf(setx,sety);break;
  case 11: obj = new Dwarf(setx,sety);break; 
  case 20: obj = new Arrow(setx,sety);break;  
  case 21: obj = new Damage_Report(setx,sety);break; 
  case 22: obj = new Tree(setx,sety);break;
  case 23: obj = new Rock(setx,sety);break;           
  }       
 obj->next = first;
 first = obj; 

 return obj;
 }
//------------------------------------------------------------------------------
 
Game_Object* Game::Create(int type,int x,int y,bool reg)
{ 
 Game_Object* obj;
 float setx, sety;
 setx = GRID_X+SLOT*(x+0.5f);
 sety = GRID_Y+SLOT*(y+0.5f);
 obj = Create(type, setx,sety);
 if (reg)
 {
  if (grid[x][y])  
  Remove(grid[x][y]);
  grid[x][y] = obj;
  }
 return obj;
 }

//------------------------------------------------------------------------------
void Game::Remove(Game_Object* obj)
{
 Game_Object* item;
 if (first==obj)
 {
  first = obj->next;
  delete obj;
  return;               
  } 
  item = first;
  while(1)
  {   
   if (item->next == obj)
   {
    item->next=obj->next;
    delete obj;
    return;       
    }
    item = item->next; 
   }
 }

//------------------------------------------------------------------------------  
void Game::Display()
{ 
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 glLoadIdentity(); 
 glColor3f(1.0f,1.0f,1.0f);   
 glEnable( GL_TEXTURE_2D );
 //draw borders
 glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[STONE]); 
 glBegin (GL_QUAD_STRIP);
 float tx = 0.0f; 
 for (int i = 0; i <= 1024 ; i += 64)
 {
  glTexCoord2d(tx,0.5f);glVertex3f(i,32.0f,100.0f);
  glTexCoord2d(tx,0.0f);glVertex3f(i,0.0f,100.0f);
  tx = tx == 0.0f ? 1.0f:0.0f;
  }   
  glEnd();
    
 glBegin (GL_QUAD_STRIP);
 tx = 0.0f; 
 for (int i = 0; i <= 1024 ; i += 64)
 {
  glTexCoord2d(tx,0.5f);glVertex3f(i,768.0f,100.0f);
  glTexCoord2d(tx,0.0f);glVertex3f(i,736.0f,100.0f);
  tx = tx == 0.0f ? 1.0f:0.0f;
  }   
  glEnd();
   
 glBegin (GL_QUAD_STRIP);
 tx = 0.0f; 
 for (int i = 0; i <= 1024 ; i += 64)
 {
  glTexCoord2d(0.25f,tx);glVertex3f(0.0f,i,100.0f);
  glTexCoord2d(0.0f,tx);glVertex3f(16.0f,i,100.0f);
  tx = tx == 0.0f ? 1.0f:0.0f;
  }   
  glEnd();
     
 glBegin (GL_QUAD_STRIP);
 tx = 0.0f; 
 for (int i = 0; i <= 1024 ; i += 64)
 {
  glTexCoord2d(0.25f,tx);glVertex3f(224.0f,i,100.0f);
  glTexCoord2d(0.0f,tx);glVertex3f(240.0f,i,100.0f);
  tx = tx == 0.0f ? 1.0f:0.0f;
  }   
  glEnd();  
     
  glBegin (GL_QUAD_STRIP);
  tx = 0.0f; 
  for (int i = 0; i <= 1024 ; i += 64)
  {
   glTexCoord2d(0.25f,tx);glVertex3f(1008.0f,i,100.0f);
   glTexCoord2d(0.0f,tx);glVertex3f(1024.0f,i,100.0f);
   tx = tx == 0.0f ? 1.0f:0.0f;
   }   
   glEnd();
   //draw field background 
   glBindTexture( GL_TEXTURE_2D, Graphic_Resources::textures[GRASS]); 
   glBegin (GL_QUAD_STRIP);
   for (int i = GRID_Y-8; i < 768 ; i += 128)
   {
    float tx = 0.0f; 
    for (int j = GRID_X-24; j < 1024; j += 128) 
    {
     glTexCoord2d(tx,1.0f);glVertex3f(j,i+128.0f,-1700.0f);
     glTexCoord2d(tx,0.0f);glVertex3f(j,i,-1700.0f);
     tx = tx == 0.0f ? 1.0f:0.0f;
     } 
    } 
   glEnd();
 
 //sidepanel rectangles and some text
 glDisable( GL_TEXTURE_2D ); 
 glColor3f(1.0f,1.0f,1.0f);   
 Draw_Rectangle_Outline(17.0f,223.0f,33.0f,150.0f,200.0f); 
 Draw_Rectangle_Outline(17.0f,223.0f,669.0f,736.0f,150.0f); 
 glColor3f(1.0f,1.0f,0.0f);   
 glRasterPos3f(90.0f,720.0f,250.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)"Target");
 glColor3f(1.0f,1.0f,1.0f);  
 glDisable(GL_TEXTURE_2D);
 
 Stats::Draw(30.0f,600.0f);
 
 
 //draw selected info
 if (active != NULL)         
 {
  char* str = new char[20];           
  glColor3f(1.0f,0.0f,0.0f);          
  if(active->hp != 0)
  Draw_Rectangle(20.0f,20.0f+200.0f*active->hp/active->maxhp,44.0f,56.0f,150.0f);   //hp bar
  glColor3f(1.0f,1.0f,0.0f);   
  glRasterPos3f(100.0f,130.0f,200.0f);
  sprintf(str,"Damage: %d - %d",active->dmg,active->dmg+active->dmg2); 
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str); 
  glRasterPos3f(100.0f,112.0f,200.0f);
  sprintf(str,"Defense: %d / %d",active->def,active->def2); 
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str); 
  glColor3f(1.0f,1.0f,1.0f);
  Draw_Rectangle_Outline(20.0f,220.0f,44.0f,56.0f,200.0f);   //hp bar outline
  sprintf(str,"%d / %d",active->hp,active->maxhp);
  glRasterPos3f(90.0f,46.0f,200.0f);
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,(const unsigned char*)str);     
  glEnable( GL_TEXTURE_2D ); // draw unit image
  Draw_Texture(active->spriteset->sprites[0][6]->images[0],8.0f,104.0f,54.0f,150.0f,100.0f);
  glDisable( GL_TEXTURE_2D );  
  delete [] str;  
  }
  
 //draw target info 
 if (target != NULL) 
 {
  glColor3f(1.0f,0.0f,0.0f);
  if(target->hp != 0)
  Draw_Rectangle(95.0f,95.0f+120.0f*target->hp/target->maxhp,700.0f,708.0f,160.0f); //hp bar
  glColor3f(1.0f,1.0f,1.0f);
  Draw_Rectangle_Outline(95.0f,215.0f,700.0f,708.0f,200.0f);  //hp bar outline
  glEnable( GL_TEXTURE_2D ); // unit image
  Draw_Texture(target->spriteset->sprites[0][6]->images[0],16.0f,80.0f,664.0f,728.0f,200.0f);
  glDisable( GL_TEXTURE_2D );   
  }
 // draw end turn button
 glColor3f(0.5f,0.3f,0.0f); 
 Draw_Rectangle(72.0f,178.0f,295.0f,320.0f,150.0f); 
 if (Mouse::Position(72,178,290,315))
 {
  glColor3f(0.9f,0.8f,0.2f); 
  if (Mouse::Button(LEFT_DOWN))
  {
   EndTurn();
   Audio::Play(PLAY_CLICK);
   }
  glColor3f(0.9f,0.9,0.3f);                              
  }
 else  
 glColor3f(0.6f,0.6f,0.2f);
 Draw_Rectangle_Outline(72.0f,178.0f,295.0f,320.0f,200.0f); 
 glRasterPos3f(80.0f,300.0f,200.0f);
 glutBitmapString(GLUT_BITMAP_HELVETICA_18,(const unsigned char*)"END TURN");   
 //draw game objects   
 glEnable( GL_TEXTURE_2D ); 
 Game_Object* current;
 current = first; 
 while (current != NULL)
 {
  current->Draw();
  current = current->next;   
  } 
 //draw grid  
 glDisable(GL_TEXTURE_2D );
 int xx, yy; 
 if (Mouse::Position(GRID_X,GRID_X+H_SLOT_NUMBER*SLOT-1,GRID_Y,GRID_Y+V_SLOT_NUMBER*SLOT-1))
    {            
     xx = (Mouse::x-GRID_X)/SLOT;
     yy = (Mouse::y-GRID_Y)/SLOT;
     glColor3f(1.0f,0.0f,0.0f);
     Draw_Rectangle_Outline(GRID_X+xx*SLOT,GRID_X+xx*SLOT+SLOT,GRID_Y+yy*SLOT,GRID_Y+yy*SLOT+SLOT,-1500.0f);   
     
     if((active_control)&&(turn))
     {
      if (Mouse::Button(LEFT_UP))
      {
       if (grid[xx][yy])
       if ((grid[xx][yy])->player)
       {
        Audio::Play(PLAY_CLICK);
        active = (Character*)grid[xx][yy];
        Select(active);
        } 
       }
      if ((Mouse::Button(RIGHT_UP))&&(active != NULL))
      {
       if ((action_zone[xx][yy])&&(active->player == 1)&&(action_zone[xx][yy] != active->movement+1))
       active->Move(xx,yy);          
       else
       if (grid[xx][yy]) 
       if ((grid[xx][yy])->player)  
       {   
        target = (Character*)grid[xx][yy]; 
        if ((active->att)&&(target->player == 2)&&(active->player == 1))  
        active->Attack(target);        
        }         
       } 
      }              
     }
 //show monement zone    
 if ((!turn)||(!active_control))
 return;  
 xx = GRID_X;
 glBegin(GL_QUADS);
 for (int i = 0; i< H_SLOT_NUMBER;i++,xx+=SLOT)
 {
  yy = GRID_Y;
  for (int j = 0; j< V_SLOT_NUMBER;j++,yy+=SLOT)
  {
   if (action_zone[i][j] > 0)
   {
    glColor4f(0.3f,1.0f,1.0f,0.25);
    glVertex3f(xx,yy,-1600.0f);
    glVertex3f(xx+SLOT,yy,-1600.0f);
    glVertex3f(xx+SLOT,yy+SLOT,-1600.0f);
    glVertex3f(xx,yy+SLOT,-1600.0f);
    }   
   }      
  }   
 glEnd(); 
}

//------------------------------------------------------------------------------ 
void Game::Update()
{ 
 if (enemy_number == 0) 
 if (Stats::level%4)
 Init(); //go to next level
 else
 new Game_Start(0);
 if ((!turn)&&(active_control))
 if (ai->AI_Act())  //wait for enemy to end his turn
 {
  delete ai;
  turn = true; 
  Stats::EndTurn();
  active = NULL;
  Game_Object* current; 
  current = first;
  while(current != NULL)
  {
   if (current->player == 1)
   active = (Character*)current;  
   current->EndTurn();
   current = current->next;  
   } 
  if (active)
  Select(active);   
  else
  new Game_Over();      
  }
  
 //perform step
 Game_Object* current, *next; 
 current = first;
 while (current != NULL)
 {
  next = current->next;
  current->Step();
  current = next;   
  }     
 }
 
//------------------------------------------------------------------------------
void Game::EndTurn()
{
 if ((!turn)||(!active_control))
 return; 
 ai = new AI();
 ai->AI_Init(); 
 turn = false;
 }
 
//------------------------------------------------------------------------------
void Game::Select(Character* obj)
{
 int xx,yy;
 xx = (int)(obj->x-GRID_X)/SLOT;
 yy = (int)(obj->y-GRID_Y)/SLOT; 
     
 for (int i = 0; i< H_SLOT_NUMBER;i++)
 for (int j = 0; j< V_SLOT_NUMBER;j++)
 action_zone[i][j] = 0;
 
 if ((obj->player == 1)||((obj->player ==2)&&(!turn)))       
 PathFinder(xx,yy,obj->movement);  
 action_zone[xx][yy] = obj->movement+1;    
 }

//------------------------------------------------------------------------------ 
void Game::PathFinder(int x, int y,int ind)
{
 ind--;
 if (ind < 1)
 return;
     
 if (x > 0)
 {
  Check(x-1,y,ind);
  if (ind > 1)
  {
   if (y > 0) 
   Check(x-1,y-1,ind-1);
   if (y < V_SLOT_NUMBER - 1)
   Check(x-1,y+1,ind-1);
   }    
  }   
 if (x < H_SLOT_NUMBER - 1)
 {
  Check(x+1,y,ind);
  if (ind > 1)
  {
   if (y > 0)        
   Check(x+1,y-1,ind-1);
   if (y < V_SLOT_NUMBER - 1)
   Check(x+1,y+1,ind-1); 
   }   
  } 
 if (y > 0)
 Check(x,y-1,ind);    
 if (y < V_SLOT_NUMBER - 1)
 Check(x,y+1,ind);       
 }

//------------------------------------------------------------------------------
void Game::Check(int x, int y,int ind)
{
 if ((grid[x][y] == NULL)&&(action_zone[x][y]<ind))
 {
  action_zone[x][y] = ind;
  if (--ind > 0)
  PathFinder(x,y,ind);
  }     
 }
 
         
