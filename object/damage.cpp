#include "damage.h"

TextReport::TextReport(float setx, float sety, std::string val, float l, float s):
    text(setx, sety, val),
    life(l),
    speed(s),
    x(setx),
    y(sety)
{
}

void TextReport::Step(float dt)
{
    if (life > 0)
    {
        life -= dt;
        y += life*speed;
        text.SetPosition(x-10.0f,y+8.0f);
    }
    else
        delete this;
 }

Damage_Report::Damage_Report(float setx, float sety, std::string val):
    TextReport(setx, sety, val, 0.9f, 2.0f)
{
    text.SetColor(glm::vec3(1.0f,0.0f,0.0f));
}

AP_Report::AP_Report(float setx, float sety, std::string val):
    TextReport(setx, sety, val, 0.9f, 1.5f)
{
    text.SetColor(glm::vec3(0.8f,0.8f,0.0f));
    text.SetScale(0.5f);
}

Effect_Report::Effect_Report(float setx, float sety, std::string val):
    TextReport(setx, sety, val, 1.0f, 1.0f)
{
    text.SetColor(glm::vec3(0.6f, 0.2f, 0.9f));
    text.SetScale(0.4f);
}




