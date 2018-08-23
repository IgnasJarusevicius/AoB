#include "mouse.h"
#include <GL/freeglut.h>

int Mouse::x;
int Mouse::y;
int Mouse::buttons;

bool Mouse::Position(float x1,float x2, float y1, float y2)
{
 if ((x >= x1)
  &&(x <= x2)
  &&(y >= y1)
  &&(y <= y2))
  return true;
  else 
  return false;   
 }

bool Mouse::Button(int action)
{
 return ((action&buttons) == 0) ? false : true;
 }
              
void Mouse::SetBut(int button, int state)
{
 int tmp;
 switch (button)
 {
        case GLUT_LEFT_BUTTON: tmp = LEFT_DOWN; break;
        case GLUT_RIGHT_BUTTON: tmp = RIGHT_DOWN; break;
        case GLUT_MIDDLE_BUTTON: tmp = MIDDLE_DOWN; break;
        default: tmp = 0;
        }   
  if (state == GLUT_UP)   
  tmp <<= 1;
  buttons |= tmp;    
 }
 
void Mouse::SetPos(int setx, int sety)
{
 x = (setx*1024)/glutGet(GLUT_WINDOW_WIDTH);
 y = 760-(sety*768)/glutGet(GLUT_WINDOW_HEIGHT);    
 }
 
void Mouse::Reset()
{
 buttons = 0;    
 }
