#include "list.h"

//------------------------------------------------------------------------------

Path::Path()
{
    count = 0;
}
//------------------------------------------------------------------------------

Path::~Path()
{
    Item* current, *next;
    current = first;
    for (int i(0); i < count; i++)
    {
        next = current->next;
        delete current;
        current = next;
    }
}
//------------------------------------------------------------------------------

void Path::Add(float x, float y)
{
    Item* temp;
    temp = first;
    first = new Item;
    first->x = x;
    first->y = y;
    first->next = temp;
    first->att = false;
    count++;
}
//------------------------------------------------------------------------------

void Path::Remove()
{
    Item* temp;
    temp = first;
    first = first->next;
    delete temp;
    count--;
}