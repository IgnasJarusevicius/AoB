//------------------------------------------------------------------------------
#include "Battle.h"
#include <cstdlib>
#include <cmath>
#include <chrono>
#include "object/object.h"
#include "audio.h"
#include "TextObj.h"
#include "stats.h"
#include "Rectangle.h"
#include "GameObject.h"
//------------------------------------------------------------------------------
Battle::Battle()
{
    first = nullptr;
    std::srand(std::time(0));
    Init();
}

//------------------------------------------------------------------------------
Battle::~Battle()
{
    //delete all Game_Object
    Game_Object* current, *next;
    current = first;
    while(current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }
    //delete other stuff
    delete activeImage;
    delete targetImage;
    delete selRect;
    for (const auto& i : background)
        delete i;
    for (const auto& i : border)
        delete i;
    for (const auto& i : txtLines)
        delete i;
    for (const auto& i : rectangles)
        delete i;
    for (const auto& i : actionZone)
        delete i;
    delete global_stats;
}

//------------------------------------------------------------------------------
int Battle::action_zone[H_SLOT_NUMBER][V_SLOT_NUMBER];
Game_Object* Battle::grid[H_SLOT_NUMBER][V_SLOT_NUMBER];
bool Battle::active_control = true;
bool Battle::turn = true;
Game_Object* Battle::first = NULL;
Character* Battle::target = NULL;
Character* Battle::active = NULL;

void Battle::Init()
{
    //delete all Game_Object
    Game_Object* obj, *next;
    obj = first;
    while(obj != NULL)
    {
        next = obj->next;
        delete obj;
        obj = next;
    }
    //reset variables
    active_control = true;
    turn = true;
    first = NULL;
    target = NULL;
    active = NULL;

    //create player team
    for (int i = 0; i< H_SLOT_NUMBER;i++)
        for (int j = 0; j< V_SLOT_NUMBER;j++)
        {
            grid[i][j] = NULL;
            action_zone[i][j] = 0;
        }
    for (int i = 0; i<8; i++)
        if (team[i] != -1)
        {
            obj = Create(team[i],i*2,0,1);
            obj->player = 1;
        }
    //create enemy team
    int ind = 4+Stats::level;
    int min = Stats::level/9;
    int max = ind/5;
    int temp;
    for (int i = 0; i< 8 ;i++ )
    {
        temp = std::rand()%max;
        if (temp < min)
            temp = min;
        if (temp > 3)
            temp = 3;
        if (temp > ind-1)
            temp = ind-1;
        if (i == 7 && temp < ind-1)
            temp = ind > 4 ? 3 : ind-1;
        obj = Create(temp*3+rand()%3,i*2,13,1);
        obj->player = 2;
        ind -= temp+1;
        if (ind == 0)
            break;
    }

    //create some obstacles
    temp = std::rand()%10;
    for (int i = 0; i < temp ; i++)
        Create(23,1+std::rand()%(H_SLOT_NUMBER-2),1+std::rand()%(V_SLOT_NUMBER-2),1);
    temp = std::rand()%10;
    for (int i = 0; i < temp ; i++)
        Create(22,1+std::rand()%(H_SLOT_NUMBER-2),1+std::rand()%(V_SLOT_NUMBER-2),1);

    activeImage = new Picture(56.0f, 102.0f, 0.0f, Graphic_Resources::textures[GRASS]);
    targetImage = new Picture(56.0f, 712.0f, 0.0f, Graphic_Resources::textures[GRASS]);
    targetImage->SetScale(0.75f);

    for (int xx = 0; xx< H_SLOT_NUMBER; xx++)
        for (int yy = 0; yy< V_SLOT_NUMBER; yy++)
        {
            actionZone.push_back(new Rectangle(GRID_X+xx*SLOT, GRID_Y+yy*SLOT, SLOT, SLOT,-999.0f));
            actionZone.back()->SetColor(glm::vec4(0.3f,1.0f,1.0f,0.25));
            actionZone.back()->Enable(false);
        }
    //field background
    for (int i = GRID_Y+56; i < 768 ; i += 128)
        for (int j = GRID_X+40; j < 1024; j += 128)
            background.push_back(new Picture(j, i, -1000.0f, Graphic_Resources::textures[GRASS]));

    border.push_back(new Picture(512.0f, 16.0f, 0.0f, Graphic_Resources::textures[STONE], 0.0f, 16.0f, 0.0f, 0.5f));
    border.push_back(new Picture(512.0f, 752.0f, 0.0f, Graphic_Resources::textures[STONE], 0.0f, 16.0f, 0.0f, 0.5f));
    border.push_back(new Picture(8.0f, 384.0f, 0.0f, Graphic_Resources::textures[STONE], 0.0f, 0.25f, 0.0f, 11.0f));
    border.push_back(new Picture(232.0f, 384.0f, 0.0f, Graphic_Resources::textures[STONE], 0.0f, 0.25f, 0.0f, 11.0f));
    border.push_back(new Picture(1016.0f, 384.0f, 0.0f, Graphic_Resources::textures[STONE], 0.0f, 0.25f, 0.0f, 11.0f));

    rectangles.push_back(new Rectangle(24.0f, 40.0f, 192.0f, 16.0f));
    rectangles.back()->SetColor(glm::vec3(1.0f,0.0f,0.0f));
    rectangles.push_back(new RectangleOutline(24.0f, 40.0f, 192.0f, 16.0f));
    rectangles.push_back(new Rectangle(95.0f, 700.0f, 120.0f, 8.0f));
    rectangles.back()->SetColor(glm::vec3(1.0f,0.0f,0.0f));
    rectangles.push_back(new RectangleOutline(95.0f, 700.0f, 120.0f, 8.0f));
    rectangles.push_back(new RectangleOutline(64.0f, 294.0f, 122.0f, 27.0f));
    rectangles.push_back(new Rectangle(65.0f, 295.0f, 120.0f, 25.0f));
    rectangles.back()->SetColor(glm::vec3(0.5f,0.3f,0.0f));
    rectangles.push_back(new RectangleOutline(17.0f, 33.0f, 206.0f, 120.0f));
    rectangles.push_back(new RectangleOutline(17.0f, 660.0f, 206.0f, 75.0f));

    txtLines.push_back(new TextObj(100.0f, 130.0f, ""));
    txtLines.back()->SetColor(glm::vec3(1.0f,1.0f,0.0f));
    txtLines.back()->SetScale(0.30f);
    txtLines.push_back(new TextObj(100.0f, 112.0f, ""));
    txtLines.back()->SetColor(glm::vec3(1.0f,1.0f,0.0f));
    txtLines.back()->SetScale(0.30f);
    txtLines.push_back(new TextObj(90.0f, 41.0f, ""));
    txtLines.back()->SetColor(glm::vec3(1.0f,1.0f,1.0f));
    txtLines.back()->SetScale(0.30f);
    txtLines.push_back(new TextObj(90.0f, 715.0f, "Target"));
    txtLines.back()->SetColor(glm::vec3(1.0f,1.0f,0.0f));
    txtLines.back()->SetScale(0.32f);
    txtLines.push_back(new TextObj(74.0f, 296.0f, "END TURN"));
    txtLines.back()->SetScale(0.40f);


    global_stats = new GlobalStatsDisplay(30.0f, 440.0f);

    selRect = new RectangleOutline(0.0f, 0.0f, SLOT, SLOT,-998.0f);
    selRect->SetColor(glm::vec3(1.0f,0.0f,0.0f));
    selRect->Enable(false);
}

//------------------------------------------------------------------------------
Game_Object* Battle::Create(int type,float setx,float sety)
{
    Game_Object* obj = nullptr;
    switch (type)
    {
        case 0: obj = new Character(setx, sety, unit_data[ORC]);break;
        case 1: obj = new Character(setx, sety, unit_data[PIRATE]);break;
        case 2: obj = new Ranged(setx, sety, unit_data[HUNTER]);break;
        case 3: obj = new Character(setx, sety, unit_data[BARBARIAN]);break;
        case 4: obj = new Character(setx, sety, unit_data[SKELWAR]);break;
        case 5: obj = new Ranged(setx, sety, unit_data[SKELARCH]);break;
        case 6: obj = new Character(setx, sety, unit_data[VIKING]);break;
        case 7: obj = new Character(setx, sety, unit_data[LAVA]);break;
        case 8: obj = new Ranged(setx, sety, unit_data[ARCHER]);break;
        case 9: obj = new Character(setx, sety, unit_data[KNIGHT]);break;
        case 10: obj = new Character(setx, sety, unit_data[DWARF]);break;
        case 11: obj = new Character(setx, sety, unit_data[DWARF]);break;
        case 20: obj = new Arrow(setx ,sety);break;
        case 21: obj = new Damage_Report(setx, sety);break;
        case 22: obj = new Tree(setx, sety);break;
        case 23: obj = new Rock(setx, sety);break;
    }
    obj->next = first;
    first = obj;
    return obj;
 }
//------------------------------------------------------------------------------

Game_Object* Battle::Create(int type,int x,int y,bool reg)
{
    Game_Object* obj;
    float setx, sety;
    setx = GRID_X+SLOT*(x+0.5f);
    sety = GRID_Y+SLOT*(y+0.5f);
    obj = Create(type, setx,sety);
    if (reg)
    {
        if (grid[x][y])
        Remove(grid[x][y]);
        grid[x][y] = obj;
    }
    return obj;
}

//------------------------------------------------------------------------------
void Battle::Remove(Game_Object* obj)
{
    Game_Object* item;
    if (first==obj)
    {
        first = obj->next;
        delete obj;
        return;
    }
    item = first;
    while(1)
    {
        if (item->next == obj)
        {
            item->next=obj->next;
            delete obj;
            return;
        }
        item = item->next;
    }
}

//------------------------------------------------------------------------------
int Battle::Update()
{
    bool no_enemies = true;
    for (Game_Object* current = Battle::first; current != NULL; current = current->next)
        if (current->player == 2)
        {
            no_enemies = false;
            break;
        }

    if (no_enemies)
    {
        if ((Stats::level++)%4)
            return battleCont;
        else
            return battleRecruit;
    }

    global_stats->Step();
    if ((!turn)&&(active_control))
    {
        if (ai.AI_Act())  //wait for enemy to end his turn
        {
            turn = true;
            Stats::EndTurn();
            active = NULL;
            Game_Object* current;
            current = first;
            while(current != NULL)
            {
                if (current->player == 1)
                active = (Character*)current;
                current->EndTurn();
                current = current->next;
            }
            if (active)
                Select(active);
            else
                return battleOver;
        }
    }
    //perform step
    Game_Object* current, *next;
    current = first;
    while (current != NULL)
    {
        next = current->next;
        current->Step();
        current = next;
    }


    //draw selected info
    if (active != NULL)
    {
        rectangles[0]->SetScale((float)active->hp/active->maxhp, 1.0f);
        rectangles[0]->Enable();
        rectangles[1]->Enable();
        txtLines[0]->SetText(std::string("Damage: ")+std::to_string(active->dmg)+ " - " + std::to_string(active->dmg+active->dmg2));
        txtLines[0]->Enable();
        txtLines[1]->SetText(std::string("Defense: ")+std::to_string(active->def)+ " / " + std::to_string(active->def2));
        txtLines[1]->Enable();
        txtLines[2]->SetText(std::to_string(active->hp)+ " / " + std::to_string(active->maxhp));
        txtLines[2]->Enable();
        activeImage->SetTexture(active->spriteset[0][6]->images[0]);
        activeImage->Enable();
    }
    else
    {
        rectangles[0]->Enable(false);
        rectangles[1]->Enable(false);
        txtLines[1]->Enable(false);
        txtLines[2]->Enable(false);
        activeImage->Enable(false);
    }

    //draw target info
    if (target != NULL)
    {
        rectangles[2]->SetScale((float)target->hp/target->maxhp, 1.0f);
        rectangles[2]->Enable();
        rectangles[3]->Enable();
        targetImage->SetTexture(target->spriteset[0][6]->images[0]);
        targetImage->Enable();
    }
    else
    {
        rectangles[2]->Enable(false);
        rectangles[3]->Enable(false);
        targetImage->Enable(false);
    }

    // draw end turn button
    if (Mouse::Position(72,178,290,315))
    {
        rectangles[4]->SetColor(glm::vec3(0.9f,0.8f,0.2f));
        txtLines[4]->SetColor(glm::vec3(0.9f,0.8f,0.2f));
        if (Mouse::Button(Mouse::LEFT_DOWN))
        {
            EndTurn();
            Audio::Play(PLAY_CLICK);
        }
        rectangles[4]->SetColor(glm::vec3(0.9f,0.9,0.3f));
        txtLines[4]->SetColor(glm::vec3(0.9f,0.9,0.3f));
    }
    else
    {
        rectangles[4]->SetColor(glm::vec3(0.6f,0.6f,0.2f));
        txtLines[4]->SetColor(glm::vec3(0.6f,0.6f,0.2f));
    }

    //draw grid
    if (Mouse::Position(GRID_X,GRID_X+H_SLOT_NUMBER*SLOT-1,GRID_Y,GRID_Y+V_SLOT_NUMBER*SLOT-1))
    {
        int xx = (Mouse::x-GRID_X)/SLOT;
        int yy = (Mouse::y-GRID_Y)/SLOT;

        selRect->SetPosition(GRID_X+xx*SLOT,GRID_Y+yy*SLOT);
        selRect->Enable();
        if((active_control)&&(turn))
        {
            if (Mouse::Button(Mouse::LEFT_UP))
            {
                if (grid[xx][yy])
                    if ((grid[xx][yy])->player)
                    {
                        Audio::Play(PLAY_CLICK);
                        active = (Character*)grid[xx][yy];
                        Select(active);
                    }
            }
            if ((Mouse::Button(Mouse::RIGHT_UP))&&(active != NULL))
            {
                if ((action_zone[xx][yy])&&(active->player == 1)&&(action_zone[xx][yy] != active->movement+1))
                {
                    active->Move(xx,yy);
                }
                else if (grid[xx][yy] && grid[xx][yy]->player)
                {
                    target = (Character*)grid[xx][yy];
                    if ((active->att)&&(target->player == 2)&&(active->player == 1))
                        active->Attack(target);
                }
            }
        }
    }
    else
        selRect->Enable(false);
    //show monement zone

    for (int i = 0; i< H_SLOT_NUMBER;i++)
        for (int j = 0; j< V_SLOT_NUMBER;j++)
            actionZone[i*V_SLOT_NUMBER+j]->Enable(action_zone[i][j] > 0);
    return 0;
}

//------------------------------------------------------------------------------
void Battle::EndTurn()
{
    if ((!turn)||(!active_control))
        return;
    ai.AI_Init();
    turn = false;
}

//------------------------------------------------------------------------------
void Battle::Select(Character* obj)
{
    int xx,yy;
    xx = (int)(obj->x-GRID_X)/SLOT;
    yy = (int)(obj->y-GRID_Y)/SLOT;

    for (int i = 0; i< H_SLOT_NUMBER;i++)
        for (int j = 0; j< V_SLOT_NUMBER;j++)
            action_zone[i][j] = 0;

    if ((obj->player == 1)||((obj->player ==2)&&(!turn)))
        PathFinder(xx,yy,obj->movement);
    action_zone[xx][yy] = obj->movement+1;
}

//------------------------------------------------------------------------------
void Battle::PathFinder(int x, int y,int ind)
{
    ind--;
    if (ind < 1)
        return;

    if (x > 0)
    {
        Check(x-1,y,ind);
        if (ind > 1)
        {
            if (y > 0)
                Check(x-1,y-1,ind-1);
            if (y < V_SLOT_NUMBER - 1)
                Check(x-1,y+1,ind-1);
        }
    }
    if (x < H_SLOT_NUMBER - 1)
    {
        Check(x+1,y,ind);
        if (ind > 1)
        {
            if (y > 0)
                Check(x+1,y-1,ind-1);
            if (y < V_SLOT_NUMBER - 1)
                Check(x+1,y+1,ind-1);
        }
    }
    if (y > 0)
        Check(x,y-1,ind);
    if (y < V_SLOT_NUMBER - 1)
        Check(x,y+1,ind);
}

//------------------------------------------------------------------------------
void Battle::Check(int x, int y,int ind)
{
    if ((grid[x][y] == NULL)&&(action_zone[x][y]<ind))
    {
        action_zone[x][y] = ind;
        if (--ind > 0)
            PathFinder(x,y,ind);
    }
}


