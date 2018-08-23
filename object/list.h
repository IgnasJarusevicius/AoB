#ifndef DS_H
#define DS_H
//------------------------------------------------------------------------------
class Path
{
 public:
        Path(); 
        ~Path();
        class Item {
              public:
                    Item* next;
                    float x,y;
                    int dir;
                    bool att;
                    }*first;  
         
        void Add(float,float); 
        void Remove();
        int count;         
 };

//------------------------------------------------------------------------------  
class Character;
 
class List
{
      public: 
              List();
              ~List(); 
              class Item {
                    public: Character* obj;
                            Item* next;
                            } ;
              Item* first;
              Item* index;
              int size;
              void Remove(Character* obj);
              void Add(Character* obj);
              Character* Get(int ind);
              Character* Get();         
      };
//------------------------------------------------------------------------------      
#endif






      
