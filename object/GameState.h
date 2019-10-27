#pragma once
#include <functional>

enum MouseAction
{
    NONE = 0,  
    LEFT_UP,
    RIGHT_UP,        
};

enum KeyboardAction
{
    KEY_OTHER = 0,
    KEY_ESC,
    KEY_SPACE
};

class GameState {
public:
    enum Event
    {    
        noEvent = 0,
        exitGame = 1,
        newGame
    };
    
    GameState() = default;
    GameState(const GameState& orig) = delete;
    virtual ~GameState() = default;
    
    virtual void HandleKey(int key) = 0;
    virtual void HandleMouse(float x, float y, MouseAction action) = 0;
    virtual Event Step(float deltaTime = 0.0f) = 0;
    virtual void Enable(bool en = true) = 0;
protected:
};


