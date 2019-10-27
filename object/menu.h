#pragma once
#include "Picture.h"
#include "TextObj.h"
#include "Rectangle.h"
#include "GameObject.h"
#include <functional>
#include "object/grid.h"
#include "GameState.h"
//------------------------------------------------------------------------------

class Rectangle;
class Character;

class MenuButton : public Picture 
{
public:
    typedef std::function<void(void)> CallbackFunction;   
    MenuButton(float xx, float yy, unsigned tex, float coordy0 = 0.0f, float coordy1 = 1.0f); 
    bool HandleMouse(float x, float y, MouseAction action);
    void SetCallback(CallbackFunction f);
protected:
    float x;
    float y;
    CallbackFunction callback;
};


class Menu : public GameState
{
public:
    Menu();
    virtual ~Menu();
    
    void HandleKey(int key) override;
    void HandleMouse(float x, float y, MouseAction action) override;
    void Enable(bool en = true) override;
    GameState::Event Step(float deltaTime = 0.0f) override;
private:
    MenuButton* backButton;
    Picture title;
    std::vector<MenuButton*> buttons;
    TextObj* txtLines;
    void ChangeItemVisibility(bool en_back, bool en_menu, bool en_txt);
    Event event;
};



