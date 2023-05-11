/*******************************************************************//*
 * Core Application class.
 * Initializing Application elements, containing the main game loop
 * and closing SDL
 *
 *********************************************************************/

#pragma once

#include <iostream>
#include <headers/ApplicationManager/ResourceManager.hpp>
#include <headers/ApplicationManager/StateManager.hpp>

class Application {
private:
//Application elements
    SDL_Window*             m_window;
    static SDL_Renderer*    s_renderer;
    static ResourceManager* s_resMan;
    static StateManager*    s_stateMan;

//Param
    static bool s_isRunning;
    int frameDelay, frameTime, frameStart;

//Init Funtions
    void initSDL();
    void initWindow();
    void initRenderer();
    void initLib();
    void initResMan();
    void initStateMan();
    void initParam();
    void customApp();

public:
    Application();
    virtual ~Application();

    static void             closeApp();
    static SDL_Renderer*    getRenderer();
    static ResourceManager* getResourceManager();
    static StateManager*    getStateManager();

    void run();
    void clear();
};