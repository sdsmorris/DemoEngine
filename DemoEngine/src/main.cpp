#include "Display/Display.h"
#include "Game/ResourceManager.h"
#include "Game/Game.h"
#include "Debug/CollisionRenderer.h"
#include "Particle/ParticleSystem.h"

//Temporary includes
#include <iostream>

int main() {
    Display::createWindow(1280, 720, "Demo Engine");

    //Init OpenGL context
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Display::setWindowBackgroundColor(0.8, 0.8, 0.8);

    ResourceManager::init();
    ResourceManager::modelShader.use();

    Game game;
    Display::setGameContext(&game);
    Display::setFogColor(0.5, 0.5, 0.5);

    CollisionRenderer::init();
    ParticleSystem::init();

    while (!Display::windowShouldClose())
    {
        Display::updateTiming();
        Display::processInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.update();

        Display::updateWindow();
    }
    Display::destroyWindow();
}