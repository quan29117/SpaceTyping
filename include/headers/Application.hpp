#pragma once

#include <iostream>
#include <headers/ResourceManager.hpp>
#include <headers/GameState/State.hpp>

class Application {
private:
//Application elements
    SDL_Window*             m_window;
    static SDL_Renderer*    s_renderer;
    static ResourceManager* s_resMan;
    static StateManager*    s_stateMan;
    
//Spec
    static bool s_isRunning;
    int frameDelay, frameTime, frameStart;

//Init Funtions
    void initSDL();
    void initWindow();
    void initRenderer();
    void initLib();
    void initResMan();
    void initStateMan();
    void initSpec();
    void customApp();

public:
    Application();
    virtual ~Application();

    static void             closeApp();
    static SDL_Renderer*    getRenderer();
    static ResourceManager* getResourceManager();
    static StateManager*    getStateManager();

    void run();
    void clean();
};