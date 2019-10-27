#include "TextObj.h"
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include "audio.h"
#include "graphic/gres.h"
#include "object/BattleGrid.h"
#include "menu.h"
#include "GameState.h"


// Create an unordered_map of three strings (that map to strings)
static std::unordered_map<int, int> keyMap = {
    {GLFW_KEY_ESCAPE, KeyboardAction::KEY_ESC},
    {GLFW_KEY_SPACE, KeyboardAction::KEY_SPACE},
};
//#define PRINT_FPS

static const int initialWidth = 1024;
static const int initialHeight = 768;

static int windowWidth = initialWidth;
static int windowHeight = initialHeight;
static float game_speed = 1.0f;

GameState* gameState = nullptr;
Menu* menu = nullptr;
BattleGrid* battle = nullptr;
GLFWwindow* window;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_KP_ADD && action == GLFW_RELEASE)
        game_speed *= game_speed < 4.0f ? 1.5f : 1.0f;
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_RELEASE)
        game_speed /= game_speed > 0.2f ? 1.5f : 1.0f;
    else if (action == GLFW_RELEASE)
        gameState->HandleKey(keyMap[key]);
}

// -------------------------------------------------------
float mouse_x;
float mouse_y;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    mouse_x = xpos * initialWidth / windowWidth;
    mouse_y = initialHeight - ypos * initialHeight /windowHeight;
    gameState->HandleMouse(mouse_x, mouse_y, MouseAction::NONE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    windowWidth = width;
    windowHeight = height;
}

void mouse_button_cb(GLFWwindow* window, int button, int action, int modkeys)
{
    if (action==GLFW_RELEASE)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            gameState->HandleMouse(mouse_x, mouse_y, MouseAction::LEFT_UP);
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            gameState->HandleMouse(mouse_x, mouse_y, MouseAction::RIGHT_UP);
    }
 /*   if (button == GLFW_MOUSE_BUTTON_MIDDLE)
        Mouse::SetBut(action == GLFW_PRESS ? BattleGrid::MIDDLE_DOWN : BattleGrid::MIDDLE_UP);*/
}

void GameEventHandler(GameState::Event evt)
{
    switch (evt)
    {
        case GameState::exitGame:
            glfwSetWindowShouldClose(window, true);
            break;
        case GameState::newGame:
            if (battle)
                delete battle;
            gameState = battle = new BattleGrid();
            menu->Enable(false);
            break;
        default:
            return;
    }
}

int main(int argc, char** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "Game", NULL, NULL);
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
    glfwSetKeyCallback(window, key_callback);

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
        stateInfo.Enable(false);
    }
    gameState = menu = new Menu();
    auto t1 = std::chrono::high_resolution_clock::now();
    float frame_counter = 0.0f;
    float timePeriod = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> dt = t2-t1;
        t1 = t2;
        auto evt = gameState->Step(dt.count()*game_speed < 0.1f ? dt.count()*game_speed : 0.1f);
        GameEventHandler(evt);
        GraphicObject::RenderAll();
        glfwSwapBuffers(window);
        glfwPollEvents();

#ifdef PRINT_FPS
        frame_counter++;
        timePeriod += dt.count();
        if (timePeriod >= 1.0f)
        {
            float fps = frame_counter/ timePeriod;
            printf("FPS: %.1f\n", fps);
            frame_counter = 0.0f;
            timePeriod = 0.0f;
        }
#endif
    }
    delete gameState;
    glfwTerminate();
    Audio::Unload();
    return 0;
}




