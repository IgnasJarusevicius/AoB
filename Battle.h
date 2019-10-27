#pragma once
#include "object/object.h"
#include "mouse.h"
#include "graphic/gres.h"
#include "controller.h"
#include "ai.h"
#include "Picture.h"

class RectangleOutline;
 
class Battle: public Controller
{
 public:
    Battle();
    ~Battle();
    static void Remove(Game_Object*);    
    static Game_Object* Create(int,float,float);
    static void Select(Character*); 
    static bool active_control;
    int Update() override;    
    static int action_zone[H_SLOT_NUMBER][V_SLOT_NUMBER];  
    static Game_Object* grid[H_SLOT_NUMBER][V_SLOT_NUMBER]; 
private:
    friend AI;
    AI ai;  
    static Game_Object* Create(int,int,int,bool);  
    void EndTurn();
    void Init();  
    static void PathFinder(int,int,int);  
    static void Check(int,int,int);
    static bool turn;   
    static Character* target;  
    static Character* active;  
    Picture* targetImage;
    Picture* activeImage;
    GameObject* global_stats;
    RectangleOutline* selRect;
    std::vector<Picture*> background;
    std::vector<Picture*> border;
    std::vector<Rectangle*> rectangles;
    std::vector<Rectangle*> actionZone;
    std::vector<TextObj*> txtLines;
    static Game_Object* first;  
}; 
