#include "list.h"
#include <stdio.h>

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
 for (int i(0); i<count;i++)
 {
  next = current->next;
  delete current;
  current = next;  
  }            
 }
//------------------------------------------------------------------------------
void Path::Add(float x,float y)
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
//------------------------------------------------------------------------------
List::List()
{
 first = NULL;
 index = NULL;
 size = 0;
 }
 
List::~List()
{
 Item* current, *next;
 current = first;
 for (int i(0); i<size;i++)
 {
  next = current->next;
  delete current;
  current = next;  
  }
 }
//------------------------------------------------------------------------------ 
void List::Add(Character* obj)
{
 Item* current;
 current = new Item;
 current->next = first;
 current->obj = obj;
 first = current; 
 index = first; 
 size++;                   
 }
//------------------------------------------------------------------------------ 
void List::Remove(Character* obj)
{
 Item* current, *previuos;   
 current = first;   
 size--; 
 if (first->obj == obj)
 {
  first = current->next;
  delete current;
  return;       
  }
 
 while (current->obj != obj)
 {
 current = current->next;
 previuos = current;
 }
 
 previuos->next = current->next;
 delete current; 
 }
//------------------------------------------------------------------------------
Character* List::Get(int ind)
{
 Item* current;  
 current = first;           
 for (int i(0);i<ind;i++)
 current = current->next;
 return current->obj;          
 }
//------------------------------------------------------------------------------ 
Character* List::Get()
{
 Item *temp;
 temp = index;
 index = index->next;
 return temp->obj;          
 }
//------------------------------------------------------------------------------ 
