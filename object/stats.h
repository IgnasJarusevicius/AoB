#pragma once

#include "Picture.h"
#include "TextObj.h"
#include "Rectangle.h"
#include "object/grid.h"
#include "GameState.h"

class Character;

class UnitStatsDisplay
{
public:
    UnitStatsDisplay(float xx, float yy);
    void ShowUnitInfo(const Character* unit);
    void Enable(bool en = true);
    void SetPosition(float xx, float yy);
    static constexpr float width = 260.0f;
    static constexpr float height = 110.0f;
private:
    Picture image;
    TextObj stats_col1; 
    TextObj stats_col2; 
    RectangleOutline border;
    Rectangle background;
    float x;
    float y;
};

class AttackListDisplay
{
    class AttackInfo
    {
    public:
        AttackInfo(float xx, float yy, const std::string &t, const std::string &s);    
        AttackInfo(const AttackInfo&) = delete;  
        AttackInfo(AttackInfo&&) = default;
        void SetState(int state);
        void Enable(bool en = true);
    private:
        const float x;
        const float y;
        RectangleOutline border;
        TextObj title;
        TextObj stats; 
    };
public:
    AttackListDisplay(float xx, float yy);
    void ShowUnitInfo(Character* unit);
    void Enable(bool en = true);
    bool HandleMouse(float x, float y, MouseAction action);
private:
    static constexpr float h_offset = 64.0f;
    static constexpr float w_offset = 160.0f;
    static constexpr float width = 150.0f;
    static constexpr float height = 64.0f;
    unsigned selected;
    Character* unit;
    std::vector<AttackInfo> attacks;
    const float x;
    const float y;
};

class UnitMovementDisplay : public GameObject
{
public:
    UnitMovementDisplay(float xx, float yy);
    ~UnitMovementDisplay();
    bool SetActive(Character* obj, const std::vector<Character*> *u);
    void SetMousePos(std::pair<int, int> pos);
    void Enable(bool en = true) override;
    void Step(float deltaTime = 0.0f) override;
private:
    Grid::GridData<Rectangle*> grid_slots;
    Grid::GridData<int> *move;  
    const Character* active;
    std::pair<int, int> mouse_pos;
    TextObj ap_display;
    const std::vector<Character*> *units;
    float x;
    float y;
};

class UnitQueueDisplay : private GameObject
{
    class QueueItem : private GameObject
    {
        friend class UnitQueueDisplay;
        QueueItem(float xx, float yy);
        void Enable(bool en = true) override;
        void SetUnit(Character* u);
        bool HandleMouse(float x, float y, MouseAction action);
        Character* unit;
        float x;
        float y;
        bool active;
        Rectangle background;
        RectangleOutline outline;
        Picture image;
    };
public:
    UnitQueueDisplay(float xx, float yy, const std::vector<Character*> &unitList, Character* const& selected);
    ~UnitQueueDisplay();
    void Enable(bool en = true) override;
    bool HandleMouse(float x, float y, MouseAction action);
    Character* GetActive() const;
    void Step(float deltaTime = 0.0f) override;
private:
    const float x;
    const float y;
    static constexpr int img_cnt = 10;
    const std::vector<Character*> &units;
    Character* const& selected;
    std::vector<QueueItem*> items;
};

