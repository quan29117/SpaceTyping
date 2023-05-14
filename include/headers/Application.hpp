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

//Progress
    static std::size_t s_score;
    static std::size_t s_wrong_count;

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

    static void setProgress(const std::size_t& score, const std::size_t& cnt);

    static void             closeApp();
    static std::size_t      getScore();
    static std::size_t      getWrongCount();
    static SDL_Renderer*    getRenderer();
    static ResourceManager* getResourceManager();
    static StateManager*    getStateManager();

    void run();
    void clear();
};