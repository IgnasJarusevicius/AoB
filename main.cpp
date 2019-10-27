#include "mouse.h"
#include "audio.h"
#include "Battle.h"
#include "graphic/gres.h"
#include "TextObj.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>

static const int initialWidth = 1024;
static const int initialHeight = 768;

static int windowWidth = initialWidth;
static int windowHeight = initialHeight;

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    xpos = xpos * initialWidth / windowWidth;
    ypos = initialHeight - ypos * initialHeight /windowHeight;
    Mouse::SetPos(xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = width;
    windowHeight = height;
}

void mouse_button_cb(GLFWwindow* window, int button, int action, int modkeys)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
        Mouse::SetBut(action == GLFW_PRESS ? Mouse::LEFT_DOWN : Mouse::LEFT_UP);
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
        Mouse::SetBut(action == GLFW_PRESS ? Mouse::RIGHT_DOWN : Mouse::RIGHT_UP);
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        Mouse::SetBut(action == GLFW_PRESS ? Mouse::MIDDLE_DOWN : Mouse::MIDDLE_UP);
}

int main(int argc, char** argv)
{
    Controller* game;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Game", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_cb);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    {
        TextObj stateInfo(375.0f, 400.0f, "LOADING...");
        stateInfo.SetColor(glm::vec3(0.8f, 0.8f, 0.2f));
        GraphicObject::RenderAll();
        glfwSwapBuffers(window);
        Graphic_Resources::Load_Graphics();
        Audio::Init();
        Mouse::Reset();
        stateInfo.Enable(false);
    }
    game = new Menu();

    auto t1 = std::chrono::high_resolution_clock::now();
    int frame_counter = 0;
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        if (game)
        {
            int ret = game->Update();
            if (ret != 0)
            {
                if (ret == menuExit)
                {
                    break;
                }
                else if (ret == menuNew)
                {
                    delete game;
                    game = new Game_Start();
                }
                else if (ret == menuResume)
                {
                    delete game;
                    game = new Game_Start();
                }
                else if (ret == battleStart)
                {
                    delete game;
                    game = new Battle();
                }
                else if (ret == gameOver)
                {
                    delete game;
                    game = new Menu();
                }
                else if (ret == selectStart || ret == battleCont)
                {
                    delete game;
                    game = new Level();
                }
                else if (ret == selectBack)
                {
                    delete game;
                    game = new Menu();
                }
                else if (ret == battleRecruit)
                {
                    delete game;
                    game = new Game_Start(0);
                }
                else if (ret == battleOver)
                {
                    delete game;
                    game = new Game_Over();
                }
            }
        }
        Mouse::Reset();
        GraphicObject::RenderAll();
        glfwSwapBuffers(window);
        glfwPollEvents();

        frame_counter++;
        auto t2 = std::chrono::high_resolution_clock::now();
        auto timePeriod = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        if (timePeriod >= 1000)
        {
            t1 = t2;
            float fps = 1000.0f*frame_counter/ timePeriod;
            printf("FPS: %.1f\n", fps);
            frame_counter = 0;
        }
    }
    delete game;
    glfwTerminate();
    Audio::Unload();
    return 0;
}




