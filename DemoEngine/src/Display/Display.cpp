#include "Display.h"
#include <iostream>
#include "Entity/Cube.h"
#include "Game/ResourceManager.h"

GLFWwindow* Display::windowHandle;
int Display::width, Display::height;
float Display::deltaTime, Display::lastFrame;
float Display::mouseLastXPos, Display::mouseLastYPos;
bool Display::mouseFirstMove;
Game* Display::game;

void Display::createWindow(int width, int height, const char* title)
{   
    mouseFirstMove = true;
    Display::game = game;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (windowHandle == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(windowHandle);
    glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(windowHandle, mouseMoveCallback);
    glfwSetScrollCallback(windowHandle, scrollWheelCallback);

    //Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }

    Display::width = width;
    Display::height = height;
    recalculateViewport();
    lastFrame = glfwGetTime();
}

void Display::setGameContext(Game* game)
{
    Display::game = game;
}

void Display::destroyWindow()
{
    glfwTerminate();
}
void Display::updateWindow()
{
    glfwSwapBuffers(windowHandle);
    glfwPollEvents();
}

void Display::processInput()
{
    //Exit if Esc is pressed
    if (glfwGetKey(windowHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(windowHandle, true);
    //Run code
    if (glfwGetKey(windowHandle, GLFW_KEY_W))
    {
        game->player.currentSpeed = -PLAYER_RUN_SPEED;
    }
    else if (glfwGetKey(windowHandle, GLFW_KEY_S))
    {
        game->player.currentSpeed = PLAYER_RUN_SPEED;
    }
    else
        game->player.currentSpeed = 0;
    //Turn code
    if (glfwGetKey(windowHandle, GLFW_KEY_D))
    {
        game->player.currentTurnSpeed = -PLAYER_TURN_SPEED;
    }
    else if (glfwGetKey(windowHandle, GLFW_KEY_A))
    {
        game->player.currentTurnSpeed = PLAYER_TURN_SPEED;
    }
    else
        game->player.currentTurnSpeed = 0;

    //Run code
    if (glfwGetKey(windowHandle, GLFW_KEY_I))
    {
        ((Cube*)game->entities[3])->currentSpeed = -PLAYER_RUN_SPEED;
    }
    else if (glfwGetKey(windowHandle, GLFW_KEY_K))
    {
        ((Cube*)game->entities[3])->currentSpeed = PLAYER_RUN_SPEED;
    }
    else
        ((Cube*)game->entities[3])->currentSpeed = 0;
    if (glfwGetKey(windowHandle, GLFW_KEY_N))
    {
        ((Cube*)game->entities[3])->yPos += 0.005;
    }
    else if (glfwGetKey(windowHandle, GLFW_KEY_B))
    {
        ((Cube*)game->entities[3])->yPos -= 0.005;
    }
    //Turn code
    if (glfwGetKey(windowHandle, GLFW_KEY_L))
    {
        ((Cube*)game->entities[3])->currentTurnSpeed = -PLAYER_TURN_SPEED;
    }
    else if (glfwGetKey(windowHandle, GLFW_KEY_J))
    {
        ((Cube*)game->entities[3])->currentTurnSpeed = PLAYER_TURN_SPEED;
    }
    else
        ((Cube*)game->entities[3])->currentTurnSpeed = 0;
    if (glfwGetKey(windowHandle, GLFW_KEY_T))
        game->entities[5]->xPos -= 2 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_G))
        game->entities[5]->xPos += 2 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_Y))
        game->entities[5]->yPos -= 2 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_H))
        game->entities[5]->yPos += 2 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_U))
        game->entities[5]->zPos += 2 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_F))
        game->entities[8]->xPos += 0.1 * deltaTime;
    if (glfwGetKey(windowHandle, GLFW_KEY_V))
        game->entities[8]->xPos -= 0.1 * deltaTime;
}

void Display::updateTiming()
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

bool Display::windowShouldClose()
{
    return glfwWindowShouldClose(windowHandle);
}

void Display::setWindowBackgroundColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}

void Display::setFogColor(float r, float g, float b)
{
    ResourceManager::modelShader.setVec3("skyColor", glm::vec3(r, g, b));
    ResourceManager::skyboxShader.setVec3("skyColor", glm::vec3(r, g, b));
}

void Display::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!mouseFirstMove)
    {
        float xMouseDelta = xpos - mouseLastXPos;
        float yMouseDelta = ypos - mouseLastYPos;
        mouseLastXPos = xpos;
        mouseLastYPos = ypos;
        game->mainCamera.calculatePitch(yMouseDelta);
        game->mainCamera.calculateAngleAroundPlayer(xMouseDelta);
        float horizontalDist = game->mainCamera.calculateHorizontalDist();
        float verticalDist = game->mainCamera.calculateVerticalDist();
        game->mainCamera.calculateCameraPosition(horizontalDist, verticalDist);
    }
    else
    {
        mouseLastXPos = xpos;
        mouseLastYPos = ypos;
        mouseFirstMove = false;
    }
}

void Display::scrollWheelCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    game->mainCamera.calculateZoom((float)yoffset);
    float horizontalDist = game->mainCamera.calculateHorizontalDist();
    float verticalDist = game->mainCamera.calculateVerticalDist();
    game->mainCamera.calculateCameraPosition(horizontalDist, verticalDist);
}

void Display::recalculateViewport()
{
    glViewport(0, 0, width, height);
}