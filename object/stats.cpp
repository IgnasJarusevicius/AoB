#include "stats.h"
#include "graphic/gres.h"
#include "object//character.h"
#include <iostream>
#include <vector>

UnitStatsDisplay::UnitStatsDisplay(float xx, float yy) :
    image(xx, yy+25, -5.0f, 80.0f, 80.0f, Graphic_Resources::textures[NOTEXTURE]),
    stats_col1(xx+10, yy+20, ""),
    stats_col2(xx+112, yy+80, ""),
    border(xx, yy, width, height, 0.0f),
    background(xx, yy, width, height, -10.0f),
    x(xx),
    y(yy)
{
    border.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    background.SetColor(glm::vec4(0.2f, 0.1f, 0.0, 0.75f));
    stats_col1.SetScale(0.32f);
    stats_col2.SetScale(0.32f);
}

void UnitStatsDisplay::ShowUnitInfo(const Character* unit)
{
    auto info = unit->GetUnitInfo();
    image.SetTile(info.image);
    std::string str("HP: " + std::to_string(info.stats.hp) + "/" + std::to_string(info.base_stats.hp)+"\n");
    str += "AP: " + std::to_string(int(info.stats.ap+0.5f)) + "/" + std::to_string(int(info.base_stats.ap+0.5f))+"\n";
    stats_col1.SetText(str);
    str = "Damage: " + std::to_string(int(info.stats.dmg_base+0.5f)) + " - " + std::to_string(int(info.stats.dmg_base+info.stats.dmg_rand+0.5f)) + "\n";
    str += "Defense: \n";
    str += "  Melee: " + std::to_string(int(info.stats.defense[0]))+"\n";
    str += "  Ranged: " + std::to_string(int(info.stats.defense[1]));
    stats_col2.SetText(str);
}

void UnitStatsDisplay::Enable(bool en)
{
    border.Enable(en);
    background.Enable(en);
    image.Enable(en);
    stats_col1.Enable(en);
    stats_col2.Enable(en);
}

void UnitStatsDisplay::SetPosition(float xx, float yy)
{
    border.SetPosition(xx, yy);
    background.SetPosition(xx, yy);
    image.SetPosition(xx, yy+25);
    stats_col1.SetPosition(xx+10, yy+20);
    stats_col2.SetPosition(xx+112, yy+80);
}

AttackListDisplay::AttackInfo::AttackInfo(float xx, float yy, const std::string &t, const std::string &s) :
    x(xx),
    y(yy),
    border(x, y, width, height, 0.0f),
    title(x+20,y+40, t),
    stats(x+5,y+20, s)
{
    title.SetScale(0.38f);
    title.SetColor(glm::vec3(0.9f, 0.9f, 0.1f));
    border.SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
    stats.SetScale(0.32f);
}

void AttackListDisplay::AttackInfo::SetState(int state)
{
    if (state == 1)
        border.SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
    else if (state == 2)
        border.SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
    else
        border.SetColor(glm::vec3(0.8f, 0.8f, 0.8f));
}

void AttackListDisplay::AttackInfo::Enable(bool en)
{
    border.Enable(en);
    title.Enable(en);
    stats.Enable(en);
}

AttackListDisplay::AttackListDisplay(float xx, float yy) :
    selected(0),
    unit(nullptr),
    x(xx),
    y(yy)
{
}

void AttackListDisplay::ShowUnitInfo(Character* u)
{
    unit = u;
    auto att = unit->GetAttackTypes();
    attacks.clear();
    float xx = 0.0f;
    for (auto& a : att)
    {
        const auto& dmg = a->GetDamage();
        std::string str("Damage: ");
        str += std::to_string(int(dmg.base+0.5f)) + " - " + std::to_string(int(dmg.base+dmg.rand+0.5f));
        str += std::string("\nAP: ") + std::to_string(a->GetAp());
        attacks.push_back(AttackInfo(x+xx, y+h_offset, a->Name(), str));
        xx += w_offset;
    }
    selected = 0;
    attacks[0].SetState(2);
    unit->SelectAttack(0);
}

void AttackListDisplay::Enable(bool en)
{
    for (auto& i : attacks)
        i.Enable(en);
}

bool AttackListDisplay::HandleMouse(float mousex, float mousey, MouseAction action)
{
    for (unsigned i = 0; i < attacks.size(); i++)
    {
        float x1 = x+i*w_offset;
        float x2 = x1+width;
        float y1 = y+h_offset;
        float y2 = y1+height;
        if ((mousex >= x1) && (mousey >= y1) && (mousex < x2) && (mousey < y2))
        {
             if (action == LEFT_UP)
             {
                 attacks[selected].SetState(0);
                 selected = i;
                 unit->SelectAttack(i);
             }
             attacks[i].SetState(1);
        }
        else if (i == selected)
            attacks[i].SetState(2);
        else
            attacks[i].SetState(0);
    }

    return false;
}

UnitMovementDisplay::UnitMovementDisplay(float xx, float yy) :
    move(nullptr),
    active(nullptr),
    mouse_pos(-1,-1),
    ap_display(0, 0, ""),
    units(nullptr),
    x(xx),
    y(yy)
{
    for (unsigned i = 0; i< grid_slots.width; i++)
        for (unsigned j = 0; j< grid_slots.height; j++)
            {
                auto obj = new Rectangle(x+i*Grid::slotSize, y+j*Grid::slotSize, Grid::slotSize, Grid::slotSize,-999.0f);
                obj->SetColor(glm::vec4(0.3f,1.0f,1.0f,0.2f));
                obj->Enable(false);
                grid_slots[i][j] = obj;
            }
    ap_display.Enable(false);
    ap_display.SetScale(0.35f);
}

UnitMovementDisplay::~UnitMovementDisplay()
{
    for (auto& obj : grid_slots)
        delete obj;
}

void UnitMovementDisplay::Step(float deltaTime)
{
    if (move && active && active->IsMoving() == false)
    {
        for (unsigned i = 0; i< grid_slots.width; i++)
            for (unsigned j = 0; j< grid_slots.height;j++)
            {
                bool enable=false;
                auto info = active->GetUnitInfo();

                if (info.player == 1)
                    enable = (*move)[i][j] <= info.stats.ap;
                grid_slots[i][j]->Enable(enable);
                grid_slots[i][j]->SetColor(glm::vec4(0.3f, 0.7f,1.0f, 0.25f));
            }
        for (auto& obj : *units)
        {
            auto info = obj->GetUnitInfo();
            const auto grid_pos = obj->GetGridPos();
            if (grid_pos.empty())
                continue;
            auto& slot = grid_slots[grid_pos[0].first][grid_pos[0].second];
            if (obj != active && info.player != 2)
                slot->Enable(false);
            if (info.player == 2 && info.stats.hp > 0)
                slot->SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 0.2f));
            else if (obj == active)
                slot->SetColor(glm::vec4(0.3f, 1.0f, 1.0f, 0.25f));
        }
    }
    else
    {
        for (auto& slot : grid_slots)
            slot->Enable(false);
    }
}

bool UnitMovementDisplay::SetActive(Character* obj, const std::vector<Character*> *u)
{
    active = obj;
    units = u;
    if (obj && (move = obj->Select()))
        return true;
    return false;
}

void UnitMovementDisplay::SetMousePos(std::pair<int, int> pos)
{
    if (mouse_pos != pos)
    {
        mouse_pos = pos;

        if (mouse_pos.first < 0 || mouse_pos.second < 0 || active->IsMoving() || (*move)[pos.first][pos.second] > 1000)
        {
            ap_display.Enable(false);
            return;
        }
        for (auto& obj : *units)
        {
            auto grid_pos = obj->GetGridPos();
            if (!grid_pos.empty() && obj->GetGridPos()[0] == pos && obj->GetUnitInfo().player == 1)
            {
                ap_display.Enable(false);
                return;
            }
        }

        ap_display.Enable();
        ap_display.SetPosition(x+pos.first*Grid::slotSize, y+pos.second*Grid::slotSize+16, -64);
        ap_display.SetText(std::to_string((*move)[pos.first][pos.second])+ " AP");
    }
}

void UnitMovementDisplay::Enable(bool en)
{
    for (auto& obj : grid_slots)
        obj->Enable(en);
    ap_display.Enable(en);
}

UnitQueueDisplay::QueueItem::QueueItem(float xx, float yy) :
    unit(nullptr),
    x(xx),
    y(yy),
    active(false),
    background(x, yy, 38, 60),
    outline(x, yy, 38, 60),
    image(x-14, yy, 0.0f, 64, 64, Tile(Graphic_Resources::textures[NOTEXTURE]))
{
    outline.Enable(false);
}

void UnitQueueDisplay::QueueItem::Enable(bool en)
{
    background.Enable(en);
    image.Enable(en);
    outline.Enable(en && active);
}

void UnitQueueDisplay::QueueItem::SetUnit(Character* u)
{
    unit = u;
    auto info = u->GetUnitInfo();
    image.SetTile(info.image);
    auto color = info.player == 1 ? glm::vec3(0.05f, 0.6f, 0.05f) : glm::vec3(0.6f, 0.05f, 0.05f);
    background.SetColor(color);
}

bool UnitQueueDisplay::QueueItem::HandleMouse(float mousex, float mousey, MouseAction action)
{
    if ((mousex >= x) && (mousex <x+40) && (mousey >= y) && (mousey < y+64))
        active = true;
    else
        active = false;
    outline.Enable(active);
    return false;
}


UnitQueueDisplay::UnitQueueDisplay(float xx, float yy, const std::vector<Character*> &unitList, Character* const& s) :
    x(xx),
    y(yy),
    units(unitList),
    selected(s)
{
    for (int i = 0; i < img_cnt; i++)
        items.push_back(new QueueItem(xx+i*40, yy));
}

UnitQueueDisplay::~UnitQueueDisplay()
{
    for (auto& i : items)
        delete i;
}

void UnitQueueDisplay::Enable(bool en)
{
    for (auto& i : items)
        i->Enable(en);
}

bool UnitQueueDisplay::HandleMouse(float mousex, float mousey, MouseAction action)
{
    for (auto i : items)
        i->HandleMouse(mousex, mousey, action);
    return false;
}

Character* UnitQueueDisplay::GetActive() const
{
    for (auto i : items)
        if(i->active)
            return i->unit;
    return nullptr;
}

void UnitQueueDisplay::Step(float deltaTime)
{
    static float time = 0.5;
    time += deltaTime;

    if (time >= 0.5f)
    {
        std::vector<float> val;
        std::vector<float> step;
        std::vector<Character*> list;
        for (auto& u : units)
        {
            auto info = u->GetUnitInfo();
            if(info.stats.hp <= 0)
                continue;
            step.push_back(float(info.base_stats.ap)/float(info.stats.ap_regen));
            list.push_back(u);
            if (u == selected)
                val.push_back(float(info.base_stats.ap)/float(info.stats.ap_regen));
            else
                val.push_back(float(info.base_stats.ap-info.stats.ap)/float(info.stats.ap_regen));
        }

        for (int i = 0; i < img_cnt; i++)
        {
            int min = 0;
            for (unsigned j=1; j < val.size(); j++)
                if (val[j] < val[min])
                    min = j;
            items[i]->SetUnit(list[min]);
            val[min] += step[min];
        }
        time = 0;
    }
}

