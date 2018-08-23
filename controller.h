#ifndef CONTROLLER_H
#define CONTROLLER_H

//------------------------------------------------------------------------------
class Controller
{
      public: virtual void Display()=0;
              virtual void Update(){};
              virtual void Key(unsigned char, int, int){};
              virtual void Init(){};
      
      };
//------------------------------------------------------------------------------    
  
class Menu : public Controller
{
      public: Menu(Controller*);
              virtual ~Menu();
              virtual void Display();            
      private: Controller* active_game;
      };
      
//------------------------------------------------------------------------------      
class Game_Start : public Controller
{
      public: Game_Start();
              Game_Start(int);
              ~Game_Start();
              void Display();
      private: Character* characters[11];
               int* team;
               int points;
               bool back;
               void Display_Info(int);
               void Unlock_Info(int);
 };

//------------------------------------------------------------------------------ 
class Loading : public Controller
{
 public: void Display();    
 };

//------------------------------------------------------------------------------ 
class Game_Over : public Controller
{
 public: Game_Over(); 
         void Display();  
 };

//------------------------------------------------------------------------------
class Level : public Controller
{
 public: Level(Controller*); 
         void Display();  
         Controller* active_game;
 };
//------------------------------------------------------------------------------ 

class How_To : public Controller
{
 public: How_To(Controller*);
         ~How_To(){}; 
         void Return();  
         virtual void Display();
         Controller* active_game;           
 }; 
          
//------------------------------------------------------------------------------  
class Credits : public How_To
{
 public: Credits(Controller* c):How_To(c){};
         void Display();        
 };           
//------------------------------------------------------------------------------       
#endif
