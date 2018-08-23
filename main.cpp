#include "game.h"
#define TIMERMS 33

Controller* game;

static void Resize(int, int );
static void Display(void);
static void Key(unsigned char key, int x, int y);
static void MouseB(int button, int state, int x, int y);
static void Timer(int);
static void MouseP(int x, int y);

/* Program entry point */
int 
main(int argc, char *argv[])
{   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(0,0);  
    glutCreateWindow("Age Of Battles"); 
     
    //glutGameModeString("1024x768:32@60");
    //glutEnterGameMode();
     
    game = new Loading();   
    glutReshapeFunc(Resize);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Key);
    glutTimerFunc(TIMERMS,Timer,0);   
    glutPassiveMotionFunc(MouseP);
    glutMotionFunc(MouseP);
    glutMouseFunc(MouseB);
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glAlphaFunc(GL_GREATER,0.1f);
   	glEnable(GL_ALPHA_TEST); 
   	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   	glEnable(GL_BLEND);
   	 	
   	glutMainLoop();
   	delete game;
   	Graphic_Resources::Delete_All();
   	Audio::Unload(); 
    return EXIT_SUCCESS;
    }

static void Resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1024.0,0.0,768.0, -1000.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    }

static void Display(void){ 
game->Display(); 
glutSwapBuffers();    
Mouse::Reset();         
}

static void Key(unsigned char key, int x, int y){
game->Key(key,x,y);
}

static void MouseB(int button, int state, int x, int y){
Mouse::SetBut(button,state);
}
 
static void Timer(int){
game->Update();
glutTimerFunc(TIMERMS,Timer,0); 
glutPostRedisplay();
}

static void MouseP(int x, int y){
Mouse::SetPos(x,y);
}

       
