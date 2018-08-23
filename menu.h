#ifndef MENU_H
#define MENU_H
#include "controller.h"

class Menu : public Controller
{
      public: Menu(Controller*);
              ~Menu();
              void Display();
              Controller* active_game;
      private: 
      };

#endif
