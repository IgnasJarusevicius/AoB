#ifndef GAME_H
#define GAME_H
#include "object/object.h"
#include <GL/freeglut.h>
#include "mouse.h"
#include "controller.h"
#include "ai.h"
#include "stats.h"
 
class Game: public Controller
{
 public:
        Game(int*);
        ~Game();
        static void Remove(Game_Object*);  
        static void Check(int,int,int);
        static void PathFinder(int,int,int);    
        void Key(unsigned char key, int x, int y);  
        static Game_Object* Create(int,float,float);
        static Game_Object* Create(int,int,int,bool);  
        static void Select(Character*);  
        void Init();  
        void EndTurn();
        void Resume_Game();
        void Display();
        void Update();  
        AI* ai;    
        static int action_zone[H_SLOT_NUMBER][V_SLOT_NUMBER];  
        static Game_Object* grid[H_SLOT_NUMBER][V_SLOT_NUMBER]; 
        static bool active_control;
        static bool turn;  
        static Game_Object* first;  
        static Character* target;   
        static Character* active;  
        static int* team; 
        static int enemy_number;         
        }; 
#endif
