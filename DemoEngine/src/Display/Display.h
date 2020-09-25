#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Game/Game.h"

class Display
{
public:
	static int width, height;
	static float deltaTime, lastFrame;
	static float mouseLastXPos, mouseLastYPos;
	static bool mouseFirstMove;
	static Game* game;
	static void createWindow(int width, int height, const char* title);
	static void setGameContext(Game* game);
	static void destroyWindow();
	static void updateWindow();
	static void processInput();
	static void updateTiming();
	static bool windowShouldClose();
	static void setWindowBackgroundColor(float r, float g, float b);
	static void setFogColor(float r, float g, float b);
	static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
	static void scrollWheelCallback(GLFWwindow* window, double xoffset, double yoffset);
private:
	static void recalculateViewport();
	static GLFWwindow* windowHandle;
};

