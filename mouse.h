#ifndef MOUSE_H
#define MOUSE_H

class Mouse
{
public: 
    enum {
        LEFT_DOWN = 0x01,
        LEFT_UP = 0x02,
        RIGHT_DOWN = 0x04,
        RIGHT_UP = 0x08,
        MIDDLE_DOWN = 0x10,
        MIDDLE_UP = 0x20,
        ANY_DOWN = 0x55,
        ANY_UP = 0xAA,
        MOUSE_ANY = 0xFF,
    };
          
    static float x;
    static float y;
    static int buttons;
    static bool Position(float x1,float x2, float y1, float y2);
    static bool Button(int action);
    static void SetPos(float setx, float sety);
    static void SetBut(int button);
    static void Reset();
};
      
#endif
