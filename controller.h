#pragma once
#include "Picture.h"
#include "TextObj.h"
#include "Rectangle.h"
#include "GameObject.h"
#include <functional>
//------------------------------------------------------------------------------

class Rectangle;
class Character;

class Controller {
public:
    Controller() = default;
    virtual ~Controller() = default ;
    virtual int Update() = 0;
protected:
    static int team[8];     
};

//------------------------------------------------------------------------------ 

class MenuButton : public GameObject, public Picture 
{
public:
    typedef std::function<void(void)> CallbackFunction;
    
    MenuButton(float xx, float yy, unsigned tex, float coordy0 = 0.0f, float coordy1 = 1.0f); 
    virtual int Step(float deltaTime = 0.0f) override;
    void SetCallback(CallbackFunction f);
    void Enable(bool en = true) override;
protected:
    float x;
    float y;
    CallbackFunction callback;
};

constexpr int menuExit = 1;
constexpr int menuResume = 2;
constexpr int menuNew = 3;
constexpr int selectStart = 4;
constexpr int selectBack = 5;
constexpr int gameOver = 6;
constexpr int battleStart = 7;
constexpr int battleCont = 8;
constexpr int battleRecruit = 9;
constexpr int battleOver = 10;

class Menu : public Controller {
public:
    Menu(bool resumeGame = false);
    virtual ~Menu();
    int Update() override;
private:
    int state;
    MenuButton* backButton;
    Picture title;
    ObjectGroup buttons;
    TextObj* txtLines;
    void ChangeItemVisibility(bool en_back, bool en_menu, bool en_txt);
};

//------------------------------------------------------------------------------      
class GlobalStatsDisplay : public GameObject
{
public:
    GlobalStatsDisplay(float x, float y);
    int Step(float delta_time = 0) override;
    void Enable(bool en = true) override;
private:
    const RectangleOutline border;
    const RectangleOutline outline_melee;
    const RectangleOutline outline_ranged;
    Rectangle rect_melee;
    Rectangle rect_ranged;
    TextObj txt_melee;
    TextObj txt_ranged;
    TextObj txt_melee_lvl;
    TextObj txt_ranged_lvl;
    TextObj txt_level;
    TextObj txt_score;
    TextObj txt_combo;
};

class Game_Start : public Controller {
public:
    Game_Start(int a = -1);
    ~Game_Start();
    virtual int Update() override;
private:
    std::vector<MenuButton*> characters;
    MenuButton* button;
    MenuButton* buttonOK;
    unsigned points;
    std::vector<MenuButton*> charsTeam;
    std::vector<TextObj*> txtLines;
    Rectangle* rectangleInfo;
    void Display_Info(int);
    void TeamRemove(int index);
    void TeamAdd(int id);
    int state;
    GlobalStatsDisplay gloabal_stats;
};

//------------------------------------------------------------------------------ 

class Game_Over : public Controller {
public:
    Game_Over();
    int Update() override;
private:
    TextObj mText;
};

//------------------------------------------------------------------------------

class Level : public Controller {
public:
    Level();
    int Update() override;
private:
    TextObj mText;
};



