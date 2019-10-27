#include "BattleGrid.h"
#include "graphic/gres.h"
#include "character.h"
#include <iostream>



BattleGrid::BattleGrid() :
    sel_rectangle(x, y, Grid::slotSize, Grid::slotSize),
    active_display(x, y-120),
    selected_display(x, y),
    attacks_display(x+280, y-135),
    active(nullptr),
    selected(nullptr),
    move_display(x, y),
    queue_display(x+250, y+575, unitList, active),
    end_turn_button(x+280, y-120),
    grid(x, y),
    end_turn(false),
    enabled(true)
{
    std::vector<Character*> playerUnits = {new Lava(1), new SkelArch(1), new Archer(1), new Viking(1), new Orc(1)};
    std::vector<Character*> enemyUnits = {new Pirate(2), new Hunter(2), new Knight(2), new SkelWar(2), new Dwarf(2), new Barbarian(2)};
    sel_rectangle.Enable(false);
    sel_rectangle.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

    for (unsigned i = 0; i < playerUnits.size(); i++)
    {
        auto u = playerUnits[i];
        unitList.push_back(u);
        float step = (float)Grid::vSlotCnt/playerUnits.size();
        u->AddToGrid(0, step/2+i*step, &grid);
    }

    for (unsigned i = 0; i < enemyUnits.size(); i++)
    {
        auto u = enemyUnits[i];
        unitList.push_back(u);
        float step = (float)Grid::vSlotCnt/enemyUnits.size();
        u->AddToGrid(Grid::hSlotCnt-1, step/2+i*step, &grid);
    }

    obsList.push_back(new Tree(14, 5, &grid));
    obsList.push_back(new Rock(5, 7, &grid));
    obsList.push_back(new Rock2(10, 3, &grid));

    active = unitList[0];
    selected_display.Enable(false);
    move_display.SetActive(active, &unitList);
    active_display.ShowUnitInfo(active);
    attacks_display.ShowUnitInfo(active);
}

void BattleGrid::HandleMouse(float mouse_x, float mouse_y, MouseAction action)
{
    if (!enabled)
        return;
    Character* unit = nullptr;
    auto grid_pos = grid.GridPos({mouse_x, mouse_y});
    bool onGrid = false;
    if ((mouse_x >= grid.x) && (mouse_y >= grid.y) && (mouse_x < grid.x+grid.width) && (mouse_y < grid.y+grid.height))
    {
        onGrid = true;
        move_display.SetMousePos(grid_pos);
        for (auto& u : unitList)
            if (u->GetGridPos() == Grid::GridObject::GridSize({grid_pos}))
            {
                unit = u;
                break;
            }
    }
    else
    {
        move_display.SetMousePos({-1, -1});
        sel_rectangle.Enable(false);
        attacks_display.HandleMouse(mouse_x, mouse_y, action);
        queue_display.HandleMouse(mouse_x, mouse_y, action);
        unit = queue_display.GetActive();
    }

    if (end_turn_button.HandleMouse(mouse_x, mouse_y, action))
        end_turn = true;

    if (unit)
    {
        auto unit_pos = unit->GetGridPos()[0];
        const float x_pos = grid.x + Grid::slotSize*unit_pos.first;
        const float y_pos = grid.y + Grid::slotSize*unit_pos.second;
        sel_rectangle.SetPosition(x_pos, y_pos,-998.0f);
        sel_rectangle.Enable();
        int  player = unit->GetUnitInfo().player;
        auto color = glm::vec3(0.1f, 0.1f, 0.1f);
        if (player == 0)
            color = glm::vec3(1.0f, 1.0f, 0.0f);
        if (player == 1)
            color = glm::vec3(0.1f, 1.0f, 0.1f);
        else if (player == 2)
            color = glm::vec3(1.0f, 0.0f, 0.0f);
        sel_rectangle.SetColor(color);
    }
    else
        sel_rectangle.Enable(false);

    if (action == LEFT_UP)
    {
        if (unit && unit != selected)
        {
            selected = unit;
            selected_display.ShowUnitInfo(unit);
            selected_display.Enable();
            auto pos = unit->GetWorldPos();
            float xx = pos.real();
            if (xx + selected_display.width > grid.x + grid.width)
                xx -= selected_display.width;
            float yy = pos.imag();
            if (yy + selected_display.height > grid.y + grid.height)
                yy -= selected_display.height;
            selected_display.SetPosition(xx, yy);
        }
        else
        {
            selected_display.Enable(false);
            selected = nullptr;
        }
    }
    else if (action == RIGHT_UP)
    {
        if (active && (active->IsMoving() || active->GetUnitInfo().player == 2))
            return;
        if (selected)
        {
            selected_display.Enable(false);
            selected = nullptr;
            return;
        }
        if (unit)
            active->Attack(unit);
        else if (onGrid)
            active->Move(grid_pos.first, grid_pos.second);
    }
    return;
}

void BattleGrid::HandleKey(int key)
{
    if (key == KEY_SPACE)
        end_turn = true;
}

void BattleGrid::Enable(bool en)
{
    sel_rectangle.Enable(en);
    active_display.Enable(en);
    move_display.Enable(en);
    attacks_display.Enable(en);
    queue_display.Enable(en);
    grid.Enable(en);
    end_turn_button.Enable(en);
    for (auto& u : unitList)
        u->Enable(en);
    for (auto& u : obsList)
        u->Enable(en);
}


void BattleGrid::EndTurn()
{
    auto* next = active;
    float min = 10.0f;
    for (auto& obj : unitList)
        if ((obj != active) || (active->GetUnitInfo().stats.ap <= 3))
        {
            auto info = obj->GetUnitInfo();
            float val = float(info.base_stats.ap-info.stats.ap)/float(info.stats.ap_regen);
            if (val < min)
            {
                next = obj;
                min = val;
            }
        }

    for (auto& obj : unitList)
        obj->EndTurn(min, obj == active);
    active = next;
    move_display.SetActive(active, &unitList);
    active_display.ShowUnitInfo(active);
    attacks_display.ShowUnitInfo(active);
    end_turn = false;
}

BattleGrid::~BattleGrid()
{
}

GameState::Event BattleGrid::Step(float deltaTime)
{
    GameObject::UpdateAll(deltaTime);
    if (!active->IsMoving())
    {
        auto info = active->GetUnitInfo();
        if (info.stats.ap < 2 || end_turn)
            EndTurn();
        else if (info.player == 2)
            AI_Act();
        else
            active_display.ShowUnitInfo(active);
    }
    return GameState::noEvent;
}

void BattleGrid::AI_Act()
{
    Character* target = nullptr;
    float target_score = 0.0f;
    auto move = active->Select();
    auto selected_info = active->GetUnitInfo();
    for (auto& obj : unitList)
    {
        auto info = obj->GetUnitInfo();
        if (info.player == 1 && info.stats.hp > 0)
        {
            auto pos = obj->GetGridPos();
            int ap_cost = (*move)[pos[0].first][pos[0].second];
            int def = info.stats.defense[selected_info.stats.dmg_type];
            float dmg = (selected_info.stats.dmg_base+selected_info.stats.dmg_rand/2)*(100-def)/100;
            dmg = dmg > info.stats.hp ? info.stats.hp : dmg;
            float score = dmg / info.base_stats.hp / ap_cost;
            if (ap_cost <= selected_info.stats.ap)
            {
                if (info.stats.hp <= selected_info.stats.dmg_base - def)
                    score *= 6;
                else if (info.stats.hp <= dmg)
                    score *= 4;
                else
                    score *= 2;
            }
            else if (selected_info.stats.dmg_type == RANGED)
                score /=2;
            if (target_score < score)
            {
                target_score = score;
                target = obj;
            }
        }
    }
    if (target)
    {
        if (!active->Attack(target))
            end_turn = true;
    }
    else
        end_turn = true;
}




















