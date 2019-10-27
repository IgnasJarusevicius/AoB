#pragma once
#include <vector>
#include "Picture.h"
#include "Rectangle.h"
#include <complex>
#include "object.h"
#include "stats.h"
#include "grid.h"
#include "GameState.h"
//------------------------------------------------------------------------------

class EndTurnButton
{
    static constexpr float width = 150.0f;
    static constexpr float height = 40.0f;
public:
    EndTurnButton(float xx, float yy) : x(xx), y(yy), border(x, y, width, height, 0.0f),title(x+20, y+7, "Wait (1AP)")
    {
        title.SetScale(0.42f);
        title.SetColor(glm::vec3(0.9f, 0.9f, 0.1f));
        border.SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
    };
    void Enable(bool en = true)
    {
        border.Enable(en);
        title.Enable(en);
    };
    bool HandleMouse(float mouse_x, float mouse_y, MouseAction action)
    {
        if ((mouse_x >= x) && (mouse_y >= y) && (mouse_x < x+width) && (mouse_y < y+height))
        {
            border.SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
            if (action == LEFT_UP)
                return true;
        }
        else
            border.SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
        return false;
    };
private:
    const float x;
    const float y;
    RectangleOutline border;
    TextObj title;
};

class BattleGrid : public GameState
{
public:
    BattleGrid();
    ~BattleGrid();
    void HandleKey(int key) override;
    void HandleMouse(float x, float y, MouseAction action) override;
    GameState::Event Step(float deltaTime = 0.0f) override;
    void Enable(bool en = true) override;
private:
    void EndTurn();
    void AI_Act();
    RectangleOutline sel_rectangle; 
    UnitStatsDisplay active_display;
    UnitStatsDisplay selected_display;
    AttackListDisplay attacks_display;
    Character* active;
    Character* selected;
    std::vector<Character*> unitList;
    std::vector<Obstacle*> obsList;
    UnitMovementDisplay move_display;
    UnitQueueDisplay queue_display;
    EndTurnButton end_turn_button;
    Grid grid;
    static constexpr float x = 80.0f;
    static constexpr float y = 128.0f;
    bool end_turn;
    bool enabled;
};
