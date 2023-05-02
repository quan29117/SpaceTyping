#pragma once

#include <iostream>
#include <headers/GameState/State.hpp>
#include <headers/ResourceManager.hpp>

class Application {
private:
//Application elements
    SDL_Window*             m_window;
    static SDL_Renderer*    m_renderer;
    static ResourceManager* m_resMan;
    
//Spec
    bool isRunning;
    int frameDelay, frameTime, frameStart;
    std::stack <State*> states;

//Init Funtions
    void initSDL();
    void initWindow();
    void initRenderer();
    void initLib();
    void initResMan();
    void initSpec();
    void customApp();

public:
    Application();
    virtual ~Application();

    static ResourceManager* getResourceManager();
    static SDL_Renderer* getRenderer();

    void run();
    void clean();
};