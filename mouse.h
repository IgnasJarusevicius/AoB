#ifndef MOUSE_H
#define MOUSE_H

#define LEFT_DOWN 0x0001
#define LEFT_UP 0x0002
#define RIGHT_DOWN 0x0004
#define RIGHT_UP 0x0008
#define MIDDLE_DOWN 0x0010
#define MIDDLE_UP 0x0020
#define MOUSE_ANY 0x00FF
#define ANY_DOWN 0x0055
#define ANY_UP 0x00AA

class Mouse
{
      public: static int x;
              static int y;
              static int buttons;
              static bool Position(float x1,float x2, float y1, float y2);
              static bool Button(int action);
              static void SetPos(int setx, int sety);
              static void SetBut(int button, int state);
              static void Reset();
      };
      
#endif
