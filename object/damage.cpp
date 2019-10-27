#include "damage.h"
#include "Battle.h"

Damage_Report::Damage_Report(float setx, float sety) : Game_Object(setx, sety, 0), text(setx, sety, "")
{
    life = 50;
    text.SetColor(glm::vec3(1.0f,0.0f,0.0f));
}

void Damage_Report::SetValue(std::string val)
{
    text.SetText(val);
}

void Damage_Report::Step()
{
    if (life > 0)
    {
        life--;
        y += life*0.05;
        text.SetPosition(x-10.0f,y+8.0f);
    }
    else
        Battle::Remove(this) ;
 }


