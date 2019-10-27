#include "audio.h"
#include "menu.h"
#include "Rectangle.h"
#include <glm/gtc/matrix_transform.hpp>
#include "stats.h"
#include "object/object.h"
#include "graphic/gres.h"

//------------------------------------------------------------------------------

Menu::Menu() :
    title(320.0f, 640.0f, 0.0f, Graphic_Resources::textures[TITLE]),
    event(Event::noEvent)
{
    MenuButton* b;
    buttons.push_back(b = new MenuButton(416, 244.0f, Graphic_Resources::textures[MENU], 0.6f, 0.8f));
    b->SetCallback([this](){event = Event::exitGame;});

    buttons.push_back(b = new MenuButton(416, 308.0f, Graphic_Resources::textures[MENU], 0.4f, 0.6f));
    b->SetCallback([this](){ChangeItemVisibility(true, false, false);});

    buttons.push_back(b = new MenuButton(416, 372.0f, Graphic_Resources::textures[MENU], 0.2f, 0.4f));
    b->SetCallback([this](){ChangeItemVisibility(true, false, true);});

    buttons.push_back(b = new MenuButton(416, 436.0f, Graphic_Resources::textures[MENU], 0.0f, 0.2f));
    b->SetCallback([this](){event = Event::newGame;});

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
    for (auto& b : buttons)
        b->Enable(en_menu);
    txtLines->Enable(en_txt);
}

void Menu::HandleKey(int key)
{
    if (key == KEY_ESC)
        event = Event::exitGame;
}

void Menu::HandleMouse(float mouse_x, float mouse_y, MouseAction action)
{
    for (auto& b : buttons)
        if (b->HandleMouse(mouse_x, mouse_y, action))
            return;
    if (backButton->HandleMouse(mouse_x, mouse_y, action))
        return;
    return;
}

Menu::~Menu()
{
    delete txtLines;
    delete backButton;
    for (auto& b : buttons)
        delete b;
}
//------------------------------------------------------------------------------

void Menu::Enable(bool en)
{
    backButton->Enable(en);
    title.Enable(en);
    for (auto& b : buttons)
        b->Enable(en);
    txtLines->Enable(en);
}

GameState::Event Menu::Step(float)
{
    return event;
}

//------------------------------------------------------------------------------

MenuButton::MenuButton(float xx, float yy, unsigned tex, float coordy0, float coordy1) :
    Picture(xx, yy, 0.0f, {tex, 0.0f, 1.0f, coordy0, coordy1}),
    x(xx),
    y(yy)
{}

//------------------------------------------------------------------------------
void MenuButton::SetCallback(CallbackFunction f)
{
    callback = f;
}

bool MenuButton::HandleMouse(float mouse_x, float mouse_y, MouseAction action)
{
    if (!enabled)
        return false;
    if ((mouse_x >= x) && (mouse_y >= y) && (mouse_x < x + width) && (mouse_y < y + height))
    {
        if (action == LEFT_UP)
        {
            Audio::Play(PLAY_CLICK);
            if (callback)
                callback();
            return true;
        }
        SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
        return false;
    }
    SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    return false;
}


