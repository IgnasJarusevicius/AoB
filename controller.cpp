#include "Battle.h"
#include "audio.h"
#include "controller.h"
#include "Rectangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include "stats.h"
#include "object/object.h"
#define POINTS 8

//------------------------------------------------------------------------------

int Controller::team[] = {0};

//------------------------------------------------------------------------------

class UnitButton : public MenuButton
{
public:
    typedef std::function<void(void)> CallbackFunction;

    UnitButton(float xx, float yy, unsigned tex):
            MenuButton(xx, yy, tex),
            outline(x-width/2, y-height/2, width-1, height)
    {

    };
    int Step(float deltaTime = 0.0f) override
    {
        if (!enabled)
        {
            outline.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
            return 0;
        }
        if (Mouse::Position(x-width/2, x + width/2, y-height/2, y + height/2))
        {
            if (Mouse::Button(Mouse::LEFT_UP))
            {
                Audio::Play(PLAY_CLICK);
                if (callback)
                    callback();
                return 1;
            }
            outline.SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
            return 0;
        }
        outline.SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
        return 0;
    };
private:
    RectangleOutline outline;
};

Menu::Menu(bool resumeGame) :
      title(512.0f, 640.0f, 0.0f, Graphic_Resources::textures[TITLE])
{
    state = 0;
    MenuButton* b;
    buttons.Add(b = new MenuButton(512, 244.0f, Graphic_Resources::textures[MENU], 0.6f, 0.8f));
    b->SetCallback([this](){state = menuExit;});

    buttons.Add(b = new MenuButton(512, 308.0f, Graphic_Resources::textures[MENU], 0.4f, 0.6f));
    b->SetCallback([this](){ChangeItemVisibility(true, false, false);});

    buttons.Add(b = new MenuButton(512, 372.0f, Graphic_Resources::textures[MENU], 0.2f, 0.4f));
    b->SetCallback([this](){ChangeItemVisibility(true, false, true);});

    buttons.Add(b = new MenuButton(512, 436.0f, Graphic_Resources::textures[MENU], 0.0f, 0.2f));
    b->SetCallback([this](){state = menuNew;});

    backButton = new MenuButton(128.0f, 52.0f, Graphic_Resources::textures[MENU], 0.8f, 1.0f);
    backButton->SetCallback([this](){ChangeItemVisibility(false, true, false);});
    backButton->Enable(false);

    txtLines = new TextObj(280.0f, 450.0f, "Mouse Left Button\n\nMouse Right Button\n\nSPACE\n\nESC");
    txtLines->AddText("Select\n\nMove / Attack\n\nEnd Turn\n\nMenu", 560.0f, 0.0f);
    txtLines->SetColor(glm::vec3(0.1f, 0.8f, 0.8f));
    txtLines->SetScale(0.6f);
    txtLines->Enable(false);
}

void Menu::ChangeItemVisibility(bool en_back, bool en_menu, bool en_txt)
{
    backButton->Enable(en_back);
    buttons.Enable(en_menu);
    txtLines->Enable(en_txt);
}

Menu::~Menu()
{
    delete txtLines;
    delete backButton;
}
//------------------------------------------------------------------------------

int Menu::Update()
{
    backButton->Step();
    buttons.Step();
    return state;
}
//------------------------------------------------------------------------------

Game_Start::Game_Start(int a) :
    points(POINTS),
    gloabal_stats(40.0f, 440.0f)
{
    state = 0;
    if (a < 0)
    {
        Stats::Init();
        button = new MenuButton(128.0f, 52.0f, Graphic_Resources::textures[MENU], 0.8f, 1.0f);
        button->SetCallback([this](){state = selectBack;});
        for (int i = 0; i < 8; i++)
            team[i] = -1;
    }
    else
    {
        points += (int)(floor((-1.0 + sqrt(1.0 + Stats::score / 62.5)) / 2.0));
        for (int i = 0; i < 8; i++)
            if (team[i] != -1)
                points -= 1 + team[i] / 3;
    }

    characters.push_back(new UnitButton(336.0f, 364.0f, unit_data[ORC].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(336.0f, 492.0f, unit_data[PIRATE].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(336.0f, 620.0f, unit_data[HUNTER].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(464.0f, 364.0f, unit_data[BARBARIAN].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(464.0f, 492.0f, unit_data[SKELWAR].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(464.0f, 620.0f, unit_data[SKELARCH].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(592.0f, 364.0f, unit_data[VIKING].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(592.0f, 492.0f, unit_data[LAVA].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(592.0f, 620.0f, unit_data[ARCHER].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(720.0f, 364.0f, unit_data[KNIGHT].spriteset[0][6]->images[0]));
    characters.push_back(new UnitButton(720.0f, 492.0f, unit_data[DWARF].spriteset[0][6]->images[0]));

    buttonOK = new MenuButton(944.0f, 52.0f, Graphic_Resources::textures[OKBUTTON]);
    buttonOK->SetCallback([this](){state = selectStart;});

    for (int i = 0; i < 8; i++)
    {
        charsTeam.push_back(new UnitButton(192+i*96, 144.0f, unit_data[ORC].spriteset[0][6]->images[0]));
        charsTeam.back()->SetCallback([this, i](){TeamRemove(i);});
        charsTeam.back()->Enable(false);
    }
    rectangleInfo = new RectangleOutline(210.0f, 230.0f, 600.0f, 30.0f);
    rectangleInfo->SetColor(glm::vec3(0.8f, 0.8f, 0.2f));

    txtLines.push_back(new TextObj(780.0f, 60.0f, ""));
    txtLines.back()->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    txtLines.back()->SetScale(0.48f);

    txtLines.push_back(new TextObj(240.0f, 235.0f, ""));
    txtLines.back()->SetColor(glm::vec3(0.5f, 1.0f, 0.2f));
    txtLines.back()->SetScale(0.40f);

    txtLines.push_back(new TextObj(650.0f, 208.0f, ""));
    txtLines.back()->SetColor(glm::vec3(0.8f, 0.8f, 0.2f));
    txtLines.back()->SetScale(0.40f);

    for (unsigned i = 0; i < characters.size(); i++)
    {
        characters[i]->Enable(Stats::unlocked & (0x0001 << i));
        characters[i]->SetCallback([this, i](){TeamAdd(i);});
    }
    gloabal_stats.Step();
}

//------------------------------------------------------------------------------

Game_Start::~Game_Start()
{
    for (unsigned i = 0; i < characters.size(); i++)
        delete characters[i];

    for (unsigned i = 0; i < charsTeam.size(); i++)
        delete charsTeam[i];

    for (const auto& i : txtLines)
        delete i;
    delete button;
    delete buttonOK;
    delete rectangleInfo;
}

//------------------------------------------------------------------------------

int Game_Start::Update()
{
    txtLines[0]->SetText(std::string("Points: ") + std::to_string(points));
    for (unsigned i = 0; i < charsTeam.size(); i++)
        charsTeam[i]->Step();

    for (unsigned i = 0; i < characters.size(); i++)
        characters[i]->Step();

    buttonOK->Enable(points != POINTS);
    buttonOK->Step();
    button->Step();

    for (unsigned i = 0; i < characters.size(); i++)
        if (Mouse::Position(256+i/3*128, 383+i/3*128, 284+i%3*128, 411+i%3*128))
        {
            Display_Info(i);
            return state;
        }

    for (unsigned i = 0; i < charsTeam.size(); i++)
        if (Mouse::Position(128+i*96, 223 + i*96, 96, 192))
            if (team[i] != -1)
            {
                Display_Info(team[i]);
                return state;
            }

    return state;
}

void Game_Start::TeamAdd(int id)
{
    if (Stats::unlocked & (1 << id))
        for (int j = 0; j < 8; j++)
            if ((team[j] == -1)&&(points >= 1u + id / 3u))
            {
                team[j] = id;
                points -= 1 + id / 3;
                charsTeam[j]->SetTexture(unit_data[id].spriteset[0][6]->images[0]);
                charsTeam[j]->Enable(true);
                Audio::Play(PLAY_CLICK);
                return;
            }
}

void Game_Start::TeamRemove(int ind)
{
    points += 1 + team[ind] / 3;
    team[ind] = -1;
    charsTeam[ind]->Enable(false);
}

//------------------------------------------------------------------------------

void Game_Start::Display_Info(int ind)
{
    if (Stats::unlocked & (1 << ind))
    {
        txtLines[1]->SetText(std::string("HP: ") + std::to_string(unit_data[ind].hp));
        txtLines[1]->AddText(std::string("Damage: ") + std::to_string(unit_data[ind].dmg_base) + " - " + std::to_string(unit_data[ind].dmg_base + unit_data[ind].dmg_var), 380.0f, 0.0f);
        txtLines[1]->AddText(std::string("Defense: ") + std::to_string(unit_data[ind].def_melee) + " / " + std::to_string(unit_data[ind].def_ranged), 900.0f, 0.0f);
        txtLines[2]->SetText(std::string("Req. points: ") + std::to_string(1 + ind / 3));
    }
    else
    {
        char a[] = {'3', '2', '2', '4', '3', '1', '4', '5'};
        char b[] = {'1', '3', '2', '1', '2', '4', '3', '1'};

        txtLines[1]->SetText("LOCKED");
        txtLines[1]->AddText(std::string("Req. Melee lv.: ") + a[ind-3], 380.0f, 0.0f);
        txtLines[1]->AddText(std::string("Req. Ranged lv.: ") + b[ind-3], 900.0f, 0.0f);
        txtLines[2]->SetText("");
    }
}
//------------------------------------------------------------------------------

Game_Over::Game_Over() : mText(360.0f, 400.0f, "GAME OVER")
{
    mText.SetColor(glm::vec3(0.8f, 0.8f, 0.2f));
}
//------------------------------------------------------------------------------

int Game_Over::Update()
{
    if (Mouse::Button(Mouse::ANY_UP))
        return gameOver;
    return 0;
}

//------------------------------------------------------------------------------

int Level::Update()
{
    if (Mouse::Button(Mouse::ANY_UP))
        return battleStart;
    return 0;
}

//------------------------------------------------------------------------------

Level::Level() : mText(450.0f, 400.0f, "")
{
    mText.SetText(std::string("Battle: ") + std::to_string(Stats::level));
    mText.SetColor(glm::vec3(0.8f, 0.8f, 0.2f));
}

//------------------------------------------------------------------------------

MenuButton::MenuButton(float xx, float yy, unsigned tex, float coordy0, float coordy1) :
    Picture(xx, yy, 0.0f, tex, 0.0f, 1.0f, coordy0, coordy1),
    x(xx),
    y(yy){}

//------------------------------------------------------------------------------
void MenuButton::SetCallback(CallbackFunction f)
{
    callback = f;
}

void MenuButton::Enable(bool en)
{
    Picture::Enable(en);
}

int MenuButton::Step(float deltaTime)
{
    if (!enabled)
        return 0;
    if (Mouse::Position(x-width/2, x + width/2, y-height/2, y + height/2))
    {
        if (Mouse::Button(Mouse::LEFT_UP))
        {
            Audio::Play(PLAY_CLICK);
            if (callback)
                callback();
            return 1;
        }
        SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
        return 0;
    }
    SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    return 0;
}

GlobalStatsDisplay::GlobalStatsDisplay(float x, float y) :
        border(x, y, 184.0f, 160.0f),
        outline_melee(x+10.0f, y+54.0f, 120.0f, 10.0f),
        outline_ranged(x+10.0f, y+18.0f, 120.0f, 10.0f),
        rect_melee(x+10.0f, y+54.0f, 120.0f, 10.0f),
        rect_ranged(x+10.0f, y+18.0f, 120.0f, 10.0f),
        txt_melee(x+10.0f, y+68.0f, "Melee"),
        txt_ranged(x+10.0f, y+33.0f, "Ranged"),
        txt_melee_lvl(x+135.0f, y+50.0f, ""),
        txt_ranged_lvl(x+135.0f, y+15.0f, ""),
        txt_level(x+50.0f, y+134.0f, ""),
        txt_score(x+20.0f, y+108.0f, ""),
        txt_combo(x+60.0f, y+93.0f, "")
    {
        txt_melee.SetColor(glm::vec3(0.8f,0.25f,0.2f));
        txt_melee.SetScale(0.32f);
        txt_ranged.SetColor(glm::vec3(0.2f,0.8f,0.15f));
        txt_ranged.SetScale(0.32f);
        rect_melee.SetColor(glm::vec3(0.8f,0.25f,0.2f));
        rect_ranged.SetColor(glm::vec3(0.2f,0.8f,0.15f));
        txt_melee_lvl.SetColor(glm::vec3(0.8f,0.25f,0.2f));
        txt_melee_lvl.SetScale(0.32f);
        txt_ranged_lvl.SetColor(glm::vec3(0.2f,0.8f,0.15f));
        txt_ranged_lvl.SetScale(0.32f);
        txt_level.SetColor(glm::vec3(0.2f,0.8f,0.8f));
        txt_level.SetScale(0.48f);
        txt_score.SetColor(glm::vec3(0.8f,0.8f,0.2f));
        txt_score.SetScale(0.48f);
        txt_combo.SetColor(glm::vec3(0.8f,0.8f,0.2f));
        txt_combo.SetScale(0.32f);
    }

int GlobalStatsDisplay::Step(float delta_time)
{
    rect_melee.SetScale((float)Stats::xp[0]/Stats::xp2[0], 1.0f);
    rect_ranged.SetScale((float)Stats::xp[1]/Stats::xp2[1], 1.0f);
    txt_melee_lvl.SetText(std::string("Lvl: ")+std::to_string(Stats::stats[0]));
    txt_ranged_lvl.SetText(std::string("Lvl: ")+std::to_string(Stats::stats[1]));
    txt_level.SetText(std::string("Battle: ")+std::to_string(Stats::level));
    txt_score.SetText(std::string("Score: ")+std::to_string(Stats::score));
    txt_combo.SetText(std::string("x")+std::to_string(Stats::multi));
    return 0;
}

void GlobalStatsDisplay::Enable(bool en)
{

}
